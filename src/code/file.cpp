/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief File IO routines.
 *
 * @copyright This file is part of July2000. 
 *            July2000 is free software: you can redistribute it and/or
 *            modify it under the terms of the GNU General Public License
 *            as published by the Free Software Foundation, either version 3
 *            of the License, or (at your own option) any later option. 
 *            July2000 is distributed in the hope that it will be useful,
 *            but WITHOUT ANY WARRANTY; without even the implied warranty
 *            of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See
 *            the GNU General Public License for more details. 
 *            You should have received a copy of the GNU General Public
 *            License along with July2000. If not, see
 *            <https://www.gnu.org/licenses/>
 */

#include "file.h"
#include "globals.h"
#include "memory.h"
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>

#ifdef CNCNET
#include <cncnet/cncnet.h>
#endif // CNCNET

int gFilesOpen = 0;

/**
 * @brief Error out and abort execution due to a file IO error.
 * @param filename Filename to display in the error message box.
 * @param nomsg Don't use error text from FAILURE.TXT.
 */
void FileFatal(const char* filename, bool nomsg)
{
        char str[256];

        // shutdown everything
        if(gVideoInit)
                PrimarySurfaceDeinit();

        if(gSound)
                SoundDeinit();

        MemoryDeinit();

        // get the error message
        if(nomsg)
                std::sprintf(str, "%s", filename);
        else
                std::sprintf(str, "%s%s", GetFailureMessage(3), filename);

        // display the message
        MessageBoxA(NULL, str, GetFailureMessage(4), MB_OK);

        // exit
        if(gDebugAbort)
                std::abort();

        std::exit(EXIT_FAILURE);
}

/**
 * @brief Check if the game CD is in the CD drive.
 * @param retries Number of times to recheck for CD before returning.
 * @return Boolean value indicating if the CD is inserted.
 */
bool FileCheckCD(unsigned char retries)
{
#ifdef CNCNET
        gForceCD = D2kIniGetBool("Options", "ForceNoCD", true);
        return RetryCD(retries);
#endif // CNCNET
        if(gSpawned && gSpawnedNoCD)
                return false;
        else
                return RetryCD(retries);
}

/**
 * @brief Check if a file exists on the CD disk.
 * @param pathname File pathname.
 * @return Boolean value indicating if the file exists on the CD disk.
 */
bool FileExistsOnCD(const char* pathname)
{
        char letter[MAX_PATH];
        bool isCD = false;

        std::strcpy(letter, pathname);

        // check if pathname has a drive letter in it
        if(std::strchr(pathname, ':') == &letter[1]) {
                // check if that drive letter is a CD
                letter[2] = '\0';
                if(GetDriveTypeA(letter) == DRIVE_CDROM) {
                        isCD = true;
                }
        } else if(GetDriveTypeA(nullptr) == DRIVE_CDROM) {
                // directory from which the game is run is a CD
                isCD = true;
        } 

        if(!isCD)
                return false;

        // find file
        WIN32_FIND_DATAA findData;
        HANDLE hFile = FindFirstFileA(pathname, &findData);

        if(hFile == INVALID_HANDLE_VALUE) {
                gCD = false;
        } else {
                FindClose(hFile);
                gCD = true;
        }

        return gCD;
}

/**
 * @brief Set the game resource paths.
 * @param filename Name of the configurations file to read the paths from.
 */
void FileSetResPath(const char* filename)
{
        FILE* file = FileOpen(filename, "rt", NULL);

        if(file) {
                if(!FileGetNextLine(file, gRES_PATH, RESPATHSIZE)) {
                        FATAL("Cannot read res path for gRES_PATH");
                } else {
                        char* newline = std::strchr(gRES_PATH, '\n');
                        if(newline)
                                *newline = '\0';
                }

                if(!FileGetNextLine(file, gMOVIES_RES_PATH, RESPATHSIZE)) {
                        DPRINTF("Cannot read res path for gMOVIES_RES_PATH\n");
                        std::strcpy(gMOVIES_RES_PATH, gRES_PATH);
                } else {
                        char* newline = std::strchr(gRES_PATH, '\n');
                        if(newline)
                                *newline = '\0';
                }

                if(!FileGetNextLine(file, gMUSIC_RES_PATH, RESPATHSIZE)) {
                        FATAL("Cannot read res path for gMUSIC_RES_PATH");
                } else {
                        char* newline = std::strchr(gMUSIC_RES_PATH, '\n');
                        if(newline)
                                *newline = '\0';
                }

                if(!FileGetNextLine(file, gMISSIONS_FOR_ONE_PLAYER_RES_PATH, RESPATHSIZE)) {
                        FATAL("Cannot read res path for gMISSIONS_FOR_ONE_PLAYER_RES_PATH");
                } else {
                        char* newline = std::strchr(gMISSIONS_FOR_ONE_PLAYER_RES_PATH, '\n');
                        if(newline)
                                *newline = '\0';
                }

#ifdef CNCNET
                if(gSpawned) {
                        std::strcpy(gMAPS_RES_PATH, "data\\maps\\");
                        FileClose(file);
                        return;
                }
#endif // CNCNET

                if(!FileGetNextLine(file, gMAPS_RES_PATH, RESPATHSIZE)) {
                        FATAL("Cannot read res path for gMAPS_RES_PATH");
                } else {
                        char* newline = std::strchr(gMAPS_RES_PATH, '\n');
                        if(newline)
                                *newline = '\0';
                }

                FileClose(file);
        }
}

/**
 * @brief Open a file.
 * @param filename Name of the file to open.
 * @param mode fopen mode to open the file in.
 * @param filepath Path to the file without the filename.
 *      Defaults to gRES_PATH if nullptr passed.
 * @return A FILE pointer to the opened stream.
 */
FILE* FileOpen(const char* filename, const char* mode, const char* filepath)
{
        char pathname[RESPATHSIZE+2];

        // assemble a pathname
        if(filepath)
                std::sprintf(pathname, "%s%s", filepath, filename);
        else
                std::sprintf(pathname, "%s%s", gRES_PATH, filename);

        // make sure the CD is there
        if(filepath
        && !std::strncmp(filepath, gMOVIES_RES_PATH, RESPATHSIZE+2)
        && !FileExistsOnCD(filename)
        && !CheckForCD(nullptr, true))
                return 0;

        // open the file
        FILE* file = std::fopen(pathname, mode);
        if(!file)
                DPRINTF("Error opening file %s (%s): %s\n", pathname, mode, std::strerror(errno));
        else
                ++gFilesOpen;

        return file; 
}

/**
 * @brief fclose wrapper.
 * @brief Close a file.
 * @param stream A FILE pointer to an open stream.
 */
void FileClose(FILE *stream)
{
        if(!std::fclose(stream))
                --gFilesOpen;
}

/**
 * @brief fread wrapper.
 * @brief Read bytes from a file.
 * @param ptr Pointer to the location to read the data to.
 * @param size Size of a single item of data.
 * @param nmemb Number of items of data to read.
 * @param stream FILE pointer to an open file to read from.
 * @return Number of bytes read on success, short item count or zero on error.
 */
std::size_t FileRead(void* ptr, std::size_t size, std::size_t nmemb, FILE *stream)
{
        return std::fread(ptr, size, nmemb, stream);
}

/**
 * @brief fwrite wrapper.
 * @brief Read bytes from a file.
 * @param ptr Pointer to the location to write the data from.
 * @param size Size of a single item of data.
 * @param nmemb Number of items of data to write.
 * @param stream FILE pointer to an open stream to write to.
 * @return Number of bytes written on success, short item count or zero on error.
 */
std::size_t FileWrite(void* ptr, std::size_t size, std::size_t nmemb, FILE* stream)
{
        return std::fwrite(ptr, size, nmemb, stream);
}

/**
 * @brief fseek wrapper.
 * @brief Set the file position indicator for a FILE.
 * @param stream FILE pointer to an open stream to set the position for.
 * @param offset The number of bytes to add to the current position.
 * @param whence Current position in the file.
 * @return Returns 0 on success, -1 on error.
 */
int FileSeek(FILE *stream, long offset, int whence)
{
        return std::fseek(stream, offset, whence);
}

/**
 * @brief fgets wrapper.
 * @brief Read a string from the file until a newline or EOF.
 * @param s Pointer to the buffer to read to.
 * @param size Number of bytes to read.
 * @param stream FILE pointer to a stream to read from.
 * @return Returns s on success, NULL on error.
 */
char* FileGetString(char* s, int size, FILE* stream)
{
        return std::fgets(s, size, stream); 
}

/**
 * @brief Read the next line from a file.
 * @param s Pointer to the end of a string.
 * @param size Number of bytes to read.
 * @param stream FILE pointer to a stream to read from.
 * @return Returns true if the read succeeds.
 */
bool FileGetNextLine(FILE* stream, char* s, std::size_t size)
{
        if(!FileGetString(s, size, stream))
                return false;

        while(true) {
                if(std::strlen(s) == size-1)
                        FATAL("Very long line");

                if((*s != '/' || s[1] != '/') && *s !='\n')
                        break;

                if(!FileGetString(s, size, stream))
                        return false;
        }

        return true;
}

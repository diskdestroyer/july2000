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

#ifndef FILE_H
#define FILE_H

#include <windows.h>
#include <cstdio>

#define RESPATHSIZE 150         ///< MAXPATH for resource paths.

extern int gFilesOpen;          ///< Number of files currently open.

void FileFatal(const char* filename, bool nomsg);
bool FileCheckCD(unsigned char retries);
bool FileExistsOnCD(const char* pathname);
void FileSetResPath(const char* filename);

FILE* FileOpen(const char* filename, const char* mode, const char* filepath);
void FileClose(FILE* stream);
std::size_t FileRead(void* ptr, std::size_t size, std::size_t nmemb, FILE* stream);
std::size_t FileWrite(void *ptr, std::size_t size, std::size_t nmemb, FILE* stream);
int FileSeek(FILE* stream, long offset, int whence); 
char* FileGetString(char* s, int size, FILE* stream);

bool FileGetNextLine(FILE* stream, char* s, std::size_t size);

#endif // FILE_H

/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief CD-related functions.
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

#include "cd.h"
#include <windows.h>
#include <cstring>

/**
 * @brief Fill a TVolumeInfo struct with data.
 * @param letter Drive letter with a colon and a trailing slash.
 * @param info Pointer to a TVolumeInfo struct to fill.
 */
void GetVolumeInfo(const char* letter, VolumeInfo* info)
{
        std::memset(info, 0, sizeof(VolumeInfo));
        info->driveType = GetDriveTypeA(letter);
        GetVolumeInformationA(letter, 
                              info->volumeName, 
                              sizeof(info->volumeName), 
                              &info->volumeSerial, 
                              NULL, 
                              NULL, 
                              info->filesystemName, 
                              sizeof(info->filesystemName));
}

/**
 * @brief Counts the number of files, directories and their total size in a given directory.
 * @param root Name of the directory to start in.
 * @param dirs Pointer to a variable that will be initialised with the total number of directories.
 * @param files Pointer to a variable that will be initialised with the total number of files.
 * @param size Pointer to a variable that will be initialised with the total size of all files in the directory.
 */
void CountFiles(const char* root, int* dirs, int* files, int* size)
{
        WIN32_FIND_DATAA findData;
        HANDLE hFile;

        hFile = FindFirstFileA(root, &findData);

        while(FindNextFileA(hFile, &findData)) {
                if(hFile == INVALID_HANDLE_VALUE)
                        break;

                // check if it's a file or a directory
                if(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                        if(strcmpi(findData.cFileName, ".")
                        && strcmpi(findData.cFileName, "..")) {
                                ++*dirs;

                                // go inside the directory
                                char newroot[MAX_PATH];
                                std::strcpy(newroot, root);
                                std::strcat(newroot, findData.cFileName);
                                std::strcat(newroot, "\\*");

                                // count files
                                CountFiles(newroot, dirs, files, size);
                        }
                } else {
                        ++*files;
                        *size += findData.nFileSizeLow;
                }
        }
}

/**
 * @brief Verify that the inserted CD is a valid Dune 2000 CD.
 * @return true if the CD is a valid Dune 2000 CD.
 */
bool VerifyCD()
{
        // get the list of all drives
        char volumeList[MAX_PATH];

        if(!GetLogicalDriveStringsA(MAX_PATH, volumeList))
                return false;

        // iterate through volume list and find a CD
        TVolumeInfo info;
        char* volumeName;

        for(volumeName = volumeList; true; volumeName += strlen(volumeName)+1) {
                if(!std::strlen(volumeName))
                        return false;

                if(GetDriveTypeA(volumeName) == DRIVE_CDROM) {
                        // get volume info and the name matches
                        GetVolumeInfo(volumeName, &info);
                        if(!std::strcmp(info.volumeName, CD_NAME))
                                break;
                }
        }

        // not a CD
        if(strcmpi(info.filesystemName, "CDFS"))
                return 0;

        // make sure it's read-only
        if(SetVolumeLabelA(volumeName, "BUBBA")) {
                SetVolumeLabelA(volumeName, info.volumeName);
                return false;
        } else {
                // count all files and verify by size
                std::strcat(volumeName, "*");

                int files = 0;
                int dirs = 0;
                int size = 0;

                CountFiles(volumeName, &files, &dirs, &size);

                return size > CD_SIZE;
        }
}

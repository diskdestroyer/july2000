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

#ifndef CD_H
#define CD_H

#define CD_NAME "DUNE2000"              ///< Dune 2000 CD volume name.
#define CD_SIZE 665600                  ///< Dune 2000 1.06 CD data size.

struct TVolumeInfo {
        int driveType;                  ///< Drive type.
        char volumeName[64];            ///< Volume name.
        unsigned long int volumeSerial; ///< Volume serial number.
        char filesystemName[64];        ///< Filesystem name.
};

void GetVolumeInfo(const char* letter, VolumeInfo* info);
void CountFiles(const char* root, int* dirs, int* files, int* size);
bool VerifyCD();

#endif // CD_H

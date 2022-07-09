/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief CnCNet INI configuration IO routines.
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

#ifndef INI_H
#define INI_H

#include <windows.h>

void IniSetString(const char* section, const char* key, const char* value, const char* fileName);
void IniSetBool(const char* section, const char* key, bool value, const char* fileName);
void IniSetInt(const char* section, const char* key, int value, const char* fileName);

void IniGetString(const char* section, const char* key, const char* defaultValue, const char* fileName, char* out, int length);
bool IniGetBool(const char* section, const char* key, bool defaultValue, const char* fileName);
int IniGetInt(const char* section, const char* key, int defaultValue, const char* fileName);

#endif // INI_H

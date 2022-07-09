/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Game configuration parsing.
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

#ifndef D2KINI_H
#define D2KINI_H

void D2kIniSetString(const char* section, const char* key, const char* value);
void D2kIniSetBool(const char* section, const char* key, bool value);
void D2kIniSetInt(const char* section, const char* key, int value);

void D2kIniGetString(const char* section, const char* key, const char* defaultValue, char* out, int length);
bool D2kIniGetBool(const char* section, const char* key, bool defaultValue);
int D2kIniGetInt(const char* section, const char* key, int defaultValue);

#endif // D2KINI_H

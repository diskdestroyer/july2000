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

#include "ini.h"
#include <windows.h>
#include <cstdio>
#include <cstring>
#include <cctype>

/**
 * @brief Write a string value to an INI file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void IniSetString(const char* section, const char* key, const char* value, const char* filename)
{
        WritePrivateProfileStringA(section, key, value, filename);
}

/**
 * @brief Write a boolean value to an INI file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void IniSetBool(const char* section, const char* key, bool value, const char* filename)
{
        IniSetString(section, key, value ? "Yes" : "No", filename);
}

/**
 * @brief Write an integer value to an INI file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void IniSetInt(const char *section, const char *key, int value, const char *filename)
{
        char result[10];
        std::sprintf(result,"%d",value);
        IniSetString(section, key, result, filename);
}

/**
 * @brief Read a string value from an INI file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @param out Output buffer to read to.
 * @param length Size of the output buffer.
 */
void IniGetString(const char* section, const char* key, const char* defaultValue, const char* filename, char* out, int length)
{
        GetPrivateProfileStringA(section, key, defaultValue, out, length, filename);
}

/**
 * @brief Read a boolean value from an INI file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @return Boolean value read.
 */
bool IniGetBool(const char* section, const char* key, bool defaultValue, const char* filename)
{
        char value[5];
        IniGetString(section, key, defaultValue ? "Yes" : "No", filename, value, sizeof(value));

        for(char *p = value; *p != '\0'; ++p)
                *p = static_cast<char>(std::tolower(*p));

        return !std::strcmp(value, "yes")
            || !std::strcmp(value, "true")
            || !std::strcmp(value, "1");
}

/**
 * @brief Read an integer value from an INI file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @return Integer value read.
 */
int IniGetInt(const char* section, const char* key, int defaultValue, const char* filename)
{
        char dvalue[10];
        char value[10];

        std::sprintf(dvalue,"%d", defaultValue);
        IniGetString(section, key, dvalue, filename, value, 10);

        return atoi(value);
}

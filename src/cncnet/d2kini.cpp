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

#include "d2kini.h"
#include "ini.h"
#include <code/globals.h>

/**
 * @brief Write a string value to the game INI configuration file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void D2kIniSetString(const char* section, const char* key, const char* value)
{
	IniSetString(section, key, value, DUNECONFIG);
}

/**
 * @brief Write a boolean value to the game INI configuration file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void D2kIniSetBool(const char* section, const char* key, bool value)
{
	IniSetBool(section, key, value, DUNECONFIG);
}

/**
 * @brief Write an integer value to the game INI configuration file.
 * @param section INI section to write to.
 * @param key INI key to write to.
 * @param value Value to write.
 * @param filename INI file to write to.
 */
void D2kIniSetInt(const char* section, const char* key, int value)
{
	IniSetInt(section, key, value, DUNECONFIG);
}

/**
 * @brief Read a string value from the game INI configuration file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @param out Output buffer to read to.
 * @param length Size of the output buffer.
 */
void D2kIniGetString(const char* section, const char* key, const char* defaultValue, char* out, int length)
{
	IniGetString(section, key, defaultValue, DUNECONFIG, out, length);
}

/**
 * @brief Read a boolean value from the game INI configuration file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @return Boolean value read.
 */
bool D2kIniGetBool(const char* section, const char* key, bool defaultValue)
{
	return IniGetBool(section, key, defaultValue, DUNECONFIG);
}

/**
 * @brief Read an integer value from the game INI configuration file.
 * @param section INI section to read from.
 * @param key INI key to read from.
 * @param defaultValue Default value to return in case of an error.
 * @param filename INI file to read from.
 * @return Integer value read.
 */
int D2kIniGetInt(const char* section, const char* key, int defaultValue)
{
	return IniGetInt(section, key, defaultValue, DUNECONFIG);
}

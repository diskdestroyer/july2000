/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Global variables.
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

#ifndef GLOBALS_H
#define GLOBALS_H

#include <windows.h>

/* 
 * some of the globals here will be moved to 
 * their appropriate files when they're done
 */

#define PIXEL_555 0xcaca        ///< RGB555.
#define PIXEL_565 0xfbce        ///< RGB565.

extern bool gDebugAbort;        ///< Use abort() instead of exit().
extern bool gDebugMemory;       ///< Enable memory debug.
extern bool gDebugRandom;       ///< Enable rand debug.

#ifdef HOOKS
#include <hooks/dump.h>
#else // !HOOKS

/* ... */

#endif // HOOKS

void DebugPrintf(const char* format, ...);
void FatalError(const char* caption, const char* format, ...);
int Random(const char* pathname, const int line);

/**
 * @def DPRINTF(format, ...)
 * @brief Variadic macro for printing a formatted debug message to stderr.
 */
#define DPRINTF(format, ...) DebugPrintf(format, ##__VA_ARGS__)

/**
 * @def FATAL(format, ...)
 * @brief Macro defaulting FatalError message box caption to the current __FUNCTION__.
 * 
 * @def RANDOM()
 * @brief Macro defaulting Random parameters to the current __FILE__ and __LINE__.
 */
#define FATAL(format, ...) FatalError(__FUNCTION__, format, ##__VA_ARGS__)
#define RANDOM() Random(__FILE__, __LINE__)

/**
 * @def DUNECONFIG
 * @brief Game configurations file.
 */
#ifndef CNCNET
#define DUNECONFIG "dune2000.cfg"
#else // CNCNET
#define DUNECONFIG "dune2000.ini"
#endif // !CNCNET
#define RESCONFIG "resource.cfg"        ///< Resource paths file.

#endif // GLOBALS_H

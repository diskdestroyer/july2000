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

#include "globals.h"
#include <cstdio>
#include <cstdlib>

bool gDebugAbort = false;
bool gDebugMemory = false;
bool gDebugRandom = false;

#ifndef HOOKS

/* ... */

extern void PrimarySurfaceDeinit();
extern void SoundDeinit();
#endif // !HOOKS
extern void MemoryDeinit();

/**
 * @brief Variadic function for printing a formatted debug message to stderr.
 * @param format Format string.
 * @param ... Arguments for the format string.
 */
void DebugPrintf(const char* format, ...)
{
#ifndef NDEBUG
        va_list arg;

        va_start(arg, format);
        std::vfprintf(stderr, format, arg);
        va_end(arg);
#endif // !NDEBUG
}

/**
 * @brief Error out and abort execution.
 * @param caption Message box caption.
 * @param format Format string.
 * @param ... Arguments for the format string.
 */
void FatalError(const char* caption, const char* format, ...)
{
        // shutdown everything
        if(gVideoInit)
                PrimarySurfaceDeinit();

        if(gSound)
                SoundDeinit();

        MemoryDeinit();

        // make a string
        va_list arg;
        char str[256];

        va_start(arg, format);
        std::vsprintf(str, format, arg);
        va_end(arg);

        // add gGameTicks to the string
        std::strcat(str, " [gGameTicks = %d]\n");
        sprintf(str, str, gGameTicks);

        // display the message
        MessageBoxA(NULL, str, caption, MB_OK);

        // exit
        if(gDebugAbort)
                std::abort();

        std::exit(EXIT_FAILURE);
}

/**
 * @brief Generate a pseudo-random number.
 * @param filename (gDebugMemory) Name of the file where the function is called.
 * @param line (gDebugMemory) Line of code where the function is called.
 * @return Pseudo-randomly generated integer value.
 */
int Random(const char* pathname, const int line)
{
        if(gDebugRandom)
                DPRINTF("%s, %d\n", pathname, line);

#ifdef HOOKS
        return crt_rand();
#else // !HOOKS
        return std::rand();
#endif // HOOKS
}

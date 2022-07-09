/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief DLL entry point.
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

#include "hook.h"
#include <windows.h>

/**
 * @def HOOKS
 * @brief Macro passed from CMake to include DLL-related code.
 */

static_assert(sizeof(void*) == 4, "Only 32-bit builds are allowed");

/**
 * @brief Main DLL entry point for initialising hooks.
 * @param hinstDLL Handle to the current DLL module.
 * @param fdwReason Reason for being called.
 * @param reserved Reserved.
 */
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
        switch(fdwReason) { 
                case DLL_PROCESS_ATTACH:
                        Start_Hooking();
                        Init_Hooks();
                        Stop_Hooking();
                        break;

                case DLL_THREAD_ATTACH:
                        break;

                case DLL_THREAD_DETACH:
                        break;

                case DLL_PROCESS_DETACH:
                        break;
        }

        return TRUE;
}

/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Functions for hooking code from the original executable.
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

/* Based on https://github.com/TheAssemblyArmada/Thyme */

#include "hook.h"
#include <windows.h>
#include <cstdint>
#include <cstring>

static const std::size_t gs_TextSize = 0x000bd000;
static DWORD gs_OriginalProtect;

/*
 * @brief Change .text memory protection to RWX.
 */
void Start_Hooking()
{
        VirtualProtect(reinterpret_cast<LPVOID>(0x00401000), gs_TextSize, PAGE_EXECUTE_READWRITE, &gs_OriginalProtect);
}

/*
 * @brief Restore original the original .text memory protection.
 */
void Stop_Hooking()
{
        DWORD dummyProtect;
        VirtualProtect(reinterpret_cast<LPVOID>(0x00401000), gs_TextSize, gs_OriginalProtect, &dummyProtect);
}

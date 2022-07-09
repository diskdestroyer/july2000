/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Code for initialising function hooks.
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
#include <code/cd.h>
#include <code/file.h>
#include <code/globals.h>
#include <code/memory.h>
#include <code/particle.h>
#include <io.h>

/**
 * @brief Hooks initialisation routine.
 */
void Init_Hooks()
{
        // CRT
        Hook_JMP(0x004b0fd0, std::fopen);
        Hook_JMP(0x004b0ff0, std::fclose);
        Hook_JMP(0x004b1070, std::fread);
        Hook_JMP(0x004b11b0, std::fwrite);
        Hook_JMP(0x004b1300, std::fseek);
        Hook_JMP(0x004b1aa0, std::fgets);
        Hook_JMP(0x004bcd80, _filelength);
        Hook_JMP(0x004bce20, _fileno);

        // cd.cpp
        Hook_JMP(0x004a61d0, GetVolumeInfo);
        Hook_JMP(0x004a637c, CountFiles);
        Hook_JMP(0x004a63d5, VerifyCD);

        // file.cpp
        Hook_JMP(0x0042b730, FileFatal);
        Hook_JMP(0x0042b7d0, FileCheckCD);
        Hook_JMP(0x0042b800, FileExistsOnCD);
        Hook_JMP(0x0042b8d0, FileSetResPath);
        Hook_JMP(0x0042ba50, FileOpen);
        Hook_JMP(0x0042bb40, FileClose);
        Hook_JMP(0x0042bb60, FileRead);
        Hook_JMP(0x0042bb80, FileWrite);
        Hook_JMP(0x0042bba0, FileSeek);
        Hook_JMP(0x0042bbc0, FileGetString);
        Hook_JMP(0x0042bbe0, FileGetNextLine);

        // globals.cpp
        Hook_JMP(0x0042b590, FatalError);
        Hook_JMP(0x00448460, Random);

        // memory.cpp
        Hook_JMP(0x0044f490, MemoryInit);
        Hook_JMP(0x0044f4d0, MemoryAlloc);
        Hook_JMP(0x0044f630, MemoryFree);
        Hook_JMP(0x0044f6f0, MemoryDeinit);

        // particle.cpp
        Hook_JMP(0x0045d440, InitParticles);
        Hook_JMP(0x0045d460, AddParticle);
        Hook_JMP(0x0045d4d0, RemoveParticle);
        Hook_JMP(0x0045d4f0, MoveParticles);
        Hook_JMP(0x0045d550, BlitParticles);
        Hook_JMP(0x0045d650, FadeParticleColour);
        Hook_JMP(0x0045d730, CreateParticles);
}

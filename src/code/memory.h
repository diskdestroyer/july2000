/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Memory allocation and diagnostics routines.
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

#ifndef MEMORY_H
#define MEMORY_H

#include <windows.h>
#include <cstdlib>

/**
 * @brief A debug struct that allows storing the
 * name of the object that occupies the memory.
 */
struct TMemoryBlock {
        char name[50];  ///< Name of the object occupying the memory.
        bool used;      ///< Is this memory used?
        size_t size;    ///< Size of the allocated memory.
        void* ptr;      ///< Pointer to the allocated memory.
};

const int kMaxMallocs = 25000;  ///< (gDebugMemory) Max number of malloc calls available.

extern HANDLE gHeap;            ///< Handle to the process heap.
extern int gTotalAllocated;     ///< (gDebugMemory) Total memory allocated.

extern int gMallocCount;                        ///< (gDebugMemory) Number of calls to malloc done.
extern int gMallocIndex;                        ///< (gDebugMemory) Latest malloc index for the mallocs array.
extern TMemoryBlock gMallocs[kMaxMallocs];      ///< (gDebugMemory) Mallocs array.


void MemoryInit();
void* MemoryAlloc(std::size_t size, const char* name);
void MemoryFree(void* ptr);
void MemoryDeinit();

#endif // MEMORY_H

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

#include "memory.h"
#include "globals.h"
#include <windows.h>
#include <cstdlib>
#include <cstring>

int gMallocIndex = 0;
TMemoryBlock gMallocs[kMaxMallocs];

HANDLE gHeap = 0;
int gMallocCount = 0;
int gTotalAllocated = 0;

/**
 * @brief Initialise the memory allocation system.
 */
void MemoryInit()
{
        gHeap = GetProcessHeap();

        if(gDebugMemory) {
                std::memset(gMallocs, 0, sizeof(gMallocs));
                gMallocIndex = 0;
        }
}

/**
 * @brief Allocate memory.
 * @param size Size of the memory region to request.
 * @param name Debug name of the object that will use the memory.
 * @return Pointer to the memory allocated.
 */
void* MemoryAlloc(std::size_t size, const char* name)
{
        if(!gDebugMemory)
                return HeapAlloc(gHeap, 0, size);

        ++gMallocCount;
        if(gMallocCount > kMaxMallocs)
                FATAL("Too many mallocs - increase kMaxMallocs");

        // find a free slot in gMallocs
        for(int i = 0; i < kMaxMallocs; ++i) {
                if(!gMallocs[i].used) {
                        gMallocIndex = i;
                        break;
                }
        }
        
        // alloc memory
        void* ptr = HeapAlloc(gHeap, 0, size);
        if(!ptr)
                FATAL("malloc(%d) returned a nullptr", size);

        // assign a name to it
        if(name)
                strncpy(gMallocs[gMallocIndex].name, name, strlen(gMallocs[gMallocIndex].name));
        else
                strncpy(gMallocs[gMallocIndex].name, "NONE", strlen(gMallocs[gMallocIndex].name));

        gMallocs[gMallocIndex].used = true;
        gMallocs[gMallocIndex].size = size;
        gMallocs[gMallocIndex].ptr = ptr;
        gTotalAllocated += size;

        DPRINTF("%s: %s (%d)\n", __FUNCTION__, gMallocs[gMallocIndex].name, gMallocs[gMallocIndex].size);

        return ptr;
}

/**
 * @brief Free a block of allocated memory.
 * @param ptr Pointer to allocated memory.
 */
void MemoryFree(void *ptr)
{
        if(!gDebugMemory) {
                HeapFree(gHeap, 0, ptr);
                return;
        }

        // find a malloc to free
        for(int i = 0; i < kMaxMallocs; ++i) {
                if(gMallocs[i].ptr == ptr) {
                        gTotalAllocated = gTotalAllocated - gMallocs[i].size;
                        gMallocs[i].used = false;
                        --gMallocCount;
                        HeapFree(gHeap, 0, ptr);
                        DPRINTF("%s: %s\n", __FUNCTION__, gMallocs[i].name);
                        return;
                }
        }

        FATAL("Cannot find malloc to free");
}

/**
 * @brief Deinitialise the memory allocation system and free all used memory blocks.
 */
void MemoryDeinit()
{
        if(!gDebugMemory)
                return; 

        // free all used mallocs
        for(int i = 0; i < kMaxMallocs; ++i) {
                if(gMallocs[i].used) {
                        DPRINTF("%s: %s (%d)\n", __FUNCTION__, gMallocs[i].name, gMallocs[i].size);
                        HeapFree(gHeap, 0, gMallocs[i].ptr);
                        gMallocs[i].used = false;
                        --gMallocCount;
                }
        }
}

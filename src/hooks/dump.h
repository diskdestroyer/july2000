/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief A dump of memory addresses and type definitions that are not yet 
 * implemented in code but are otherwise needed.
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

#ifndef DUMP_H
#define DUMP_H

#include "hook.h"

// globals
#define gTabBarHeight                           Make_Global<int>		        (0x004e41dc)
#define gSound                                  Make_Global<int>		        (0x004eb00c)
#define gBitsPerPixel                           Make_Global<int>		        (0x004eb018)
#define gSpawned                                Make_Global<bool>		        (0x004e8be4)
#define gRES_PATH                               Make_Global<char[152]>		        (0x00513488)
#define gMOVIES_RES_PATH                        Make_Global<char[152]>		        (0x00513520)
#define gMUSIC_RES_PATH                         Make_Global<char[152]>		        (0x005135b8)
#define gMISSIONS_FOR_ONE_PLAYER_RES_PATH       Make_Global<char[152]>		        (0x00513650)
#define gMAPS_RES_PATH                          Make_Global<char[152]>		        (0x005136e8)
#define gVideoInit                              Make_Global<bool>		        (0x00513480)
#define gGameTicks                              Make_Global<int>		        (0x005173f4)
#define gGameMap                                Make_Global<GameMap>		        (0x00517de8)
#define gCellRows                               Make_Global<int[80]>		        (0x00547df0)
#define gTilesetResource                        Make_Global<TImage*[800]>	        (0x006d9b58)
#define gViewportHeight                         Make_Global<int>		        (0x006dc538)
#define gViewportWidth                          Make_Global<int>		        (0x00786d48)
#define gForceCD                                Make_Global<int>		        (0x00797e30)
#define gFadePalette                            Make_Global<unsigned char*[0x2000]>	(0x00795550)
#define gCD                                     Make_Global<bool>		        (0x00797e2c)
#define gSpawnedNoCD                            Make_Global<bool>		        (0x00797df0)
#define gPixel                                  Make_Global<int>		        (0x00798384)
#define gViewportX                              Make_Global<int>		        (0x00798538)
#define gViewportY                              Make_Global<int>		        (0x0079853c)

// CRT functions
#define crt_rand                                Make_cdecl<int>		                (0x004b1810)

// functions
#define SoundDeinit                             Make_cdecl<void>		        (0x0046f490)
#define GetFailureMessage                       Make_cdecl<const char*, int>	        (0x0046f490)
#define RetryCD                                 Make_cdecl<bool, char>		        (0x00482690)
#define CheckForCD                              Make_cdecl<bool, void*, bool>	        (0x00492c40)
#define PrimarySurfaceDeinit                    Make_cdecl<void>		        (0x004a4530)

// structs and classes
struct TImagePalette {
        bool used;
        char* data;
};

struct TImage {
       int width;
       int height;
       int right;
       int bottom;
       char* buffer;
       TImagePalette *palette;
       char bitdepth;
};

struct Tile {
        short index;
        int flags;
        char shroud;
        char damage;
};

struct GameMap {
        int width;
        int height;
        Tile map[16384];
};

#endif // DUMP_H

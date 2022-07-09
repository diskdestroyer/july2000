/**
 * @file
 *
 * @author diskdestroyer
 *
 * @brief Particle system.
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

#include "particle.h"
#include "globals.h"
#include <cstdlib>

int gParticleCount = 0;
TParticle gParticles[kMaxParticles];

/**
 * @brief Initialise the particle array.
 */
void InitParticles()
{
        gParticleCount = 0;
        for(int i = 0; i < kMaxParticles; ++i)
                gParticles[i].used = false;
}

/**
 * @brief Create a new particle.
 * @param x Particle initial X position.
 * @param y Particle initial Y position.
 * @param stepX Particle X displacement per one step.
 * @param stepY Particle Y displacement per one step.
 * @param steps Steps the particle can perform.
 * @param colour 8-bit or 16-bit particle colour.
 */
void AddParticle(float x, float y, float stepX, float stepY, int steps, short colour)
{
        if(gParticleCount < kMaxParticles) {
                for(int i = 0; i < kMaxParticles; ++i) {
                        TParticle* particle = &gParticles[i];
                        if(!particle->used) {
                                particle->x = x;
                                particle->y = y;
                                particle->stepX = stepX;
                                particle->stepY = stepY;
                                particle->used = true;
                                particle->steps = steps;
                                particle->colour = colour;

                                ++gParticleCount;
                                break;
                        }
                }
        }
}

/**
 * @brief Remove a particle.
 * @param particle Particle to remove.
 * @return New particle count.
 */
int RemoveParticle(TParticle* particle)
{
        particle->used = false;
        return --gParticleCount;
}

/**
 * @brief Move all particles one step.
 */
void MoveParticles()
{
        if(!gParticleCount)
                return;

        for(int i = 0; i < kMaxParticles; ++i) {
                Particle* particle = &gParticles[i]; 
                if(particle->used) {
                        if(particle->steps) {
                                particle->x += particle->stepX;
                                particle->x += particle->stepY;
                                particle->steps--;
                        } else {
                                RemoveParticle(particle);
                        }
                }
        }
}

/**
 * @brief Blit all particles to a surface.
 * @param dest Surface to blit the particles to.
 */
void BlitParticles(TImage *dest)
{
        if(!gParticleCount)
                return;

        for(int i = 0; i < kMaxParticles; ++i) {
                TParticle* particle = &gParticles[i];
                if(!particle->used)
                        continue;

                int px = static_cast<int>(particle->x);
                int py = static_cast<int>(particle->y);

                // make sure that the particle is within the viewport
                int x = px - gViewportX;
                int y = py + gTabBarHeight - gViewportY;

                if(x > 0
                && x < gViewportWidth
                && y > gTabBarHeight
                && y < gViewportHeight + gTabBarHeight) {

                        // don't blit onto shroud tiles
                        if(!gGameMap.map[px/32 + gCellRows[py/32]].shroud) {
                                if(dest->bitdepth == 16) {
                                        // get a pointer into the image
                                        unsigned short* p = reinterpret_cast<unsigned short*>
                                                            (&dest->buffer[2 * (dest->width * y + x)]);
                                        // put pixel
                                        *p = static_cast<unsigned short>(particle->colour);
                                } else { // 8
                                        // get a pointer into the image
                                        unsigned char* p = reinterpret_cast<unsigned char*>
                                                           (&dest->buffer[dest->width * y + x]);
                                        // put pixel
                                        *p = static_cast<unsigned char>(particle->colour);
                                }
                        }
                }
        }
}

/**
 * @brief Fade a 16-bit particle colour.
 * @param rgb16 Original 16-bit colour.
 * @param val Float coefficient to fade the colour with.
 */
unsigned short FadeParticleColour(unsigned short rgb16, float val)
{
        unsigned char red;
        unsigned char green;
        unsigned char blue;

        // unpack colours
        if(gPixel == PIXEL_555) {
                red = static_cast<unsigned char>(rgb16 >> 10 & 0x1f);
                green = static_cast<unsigned char>(rgb16 >> 5 & 0x1f);
                blue = static_cast<unsigned char>(rgb16 & 0x1f);
        } else { // PIXEL_565
                red = static_cast<unsigned char>(rgb16 >> 11 & 0x1f);
                green = static_cast<unsigned char>(rgb16 >> 5 & 0x3f);
                blue = static_cast<unsigned char>(rgb16 & 0x1f);
        }

        // fade colours
        red = static_cast<unsigned char>(static_cast<float>(red) * val);
        green = static_cast<unsigned char>(static_cast<float>(green) * val);
        blue = static_cast<unsigned char>(static_cast<float>(blue) * val);

        // pack colours
        if(gPixel == PIXEL_555)
                return (red << 10) | (green << 5) | blue;
        else // PIXEL_565
                return (red << 11) | (green << 5) | blue;
}

/**
 * @brief Create particles at the given screen coordinates.
 * @param x X screen coordinate.
 * @param y Y screen coordinate.
 */
void CreateParticles(int x, int y)
{
        for(int i = 0; i < PARTICLE_BATCH; ++i) {
                int spreadX = 12 - RANDOM() % 25;
                int spreadY = 12 - RANDOM() % 25;

                // round off the particle dispersion
                if(spreadX * spreadX + spreadY * spreadY < 12*12) {
                        float newX = static_cast<float>(x + spreadX); 
                        float newY = static_cast<float>(y + spreadY);

                        float stepX = RANDOM() % 200 * 0.001f;
                        float stepY = RANDOM() % 200 * 0.001f;

                        if(spreadX < 0)
                                stepX = -stepX;
                        if(spreadY < 0)
                                stepY = -stepY;

                        // get the image of the tile at xy
                        TImage* tile = gTilesetResource[gGameMap.map[x/32 + gCellRows[y/32]].index];

                        // use only first 5 bits (for a 32x32 tile)
                        unsigned char pixelX = std::abs(x) & 0b11111;
                        unsigned char pixelY = std::abs(y) & 0b11111;

                        // get a pixel from the tile image and fade it
                        unsigned short colour;
                        if(tile->bitdepth == 16)
                                colour = FadeParticleColour(*reinterpret_cast<unsigned short*>
                                                           (&tile->buffer[2 * (tile->width * pixelY + pixelX)]),
                                                           PARTICLE_FADE);
                        else // 8
                                colour = (*gFadePalette)[*reinterpret_cast<unsigned char*>
                                                        (&tile->buffer[tile->width * pixelY + pixelX]) + 512];

                        AddParticle(newX, newY, stepX, stepY, RANDOM() % 30 + PARTICLE_STILL_STEPS, colour);
                        AddParticle(newX, newY, 0.0, 0.0, RANDOM() % 30 + PARTICLE_MOVE_STEPS, colour); 
                }
        }
}

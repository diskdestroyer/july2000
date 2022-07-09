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

#ifndef PARTICLE_H
#define PARTICLE_H

#define PARTICLE_BATCH 4                ///< Particles created per CreateParticles call.

#define PARTICLE_STILL_STEPS 10         ///< Steps a still particle has on creation.
#define PARTICLE_MOVE_STEPS 50          ///< Steps a moving particle has on creation.

#define PARTICLE_FADE 0.85f             ///< Particle colour fade coefficient.

const int kMaxParticles = 4096;         ///< Max number of particles.

struct TParticle {
        float x;                ///< Initial particle x position.
        float y;                ///< Initial particle y position.
        float stepX;            ///< Value added to the particle x position every step.
        float stepY;            ///< Value added to the particle y position every step.
        unsigned int steps;     ///< Number of steps left.
        unsigned short colour;  ///< Particle colour.
        bool used;              ///< Is particle being used.
};

extern int gParticleCount;                      ///< Number of particles currently used.
extern TParticle gParticles[kMaxParticles];     ///< Particle array.

struct TImage;

void InitParticles();
void AddParticle(float x, float y, float stepX, float stepY, int step, short colour);
int RemoveParticle(Particle* particle);
void MoveParticles();
void BlitParticles(TImage* dest);
unsigned short FadeParticleColour(unsigned short rgb16, float val);
void CreateParticles(int x, int y);

#endif // PARTICLE_H

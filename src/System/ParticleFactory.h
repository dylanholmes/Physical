#ifndef PARTICLEFACTORY_H
#define PARTICLEFACTORY_H

#include <assert.h>
#include <iostream>

#include "Particle.h"

// forward definitions
class UnaryForce;
class DampedSpringForce;

class ParticleFactory {
// Particle
 public:
    static struct Particle *createParticle(float m, float *x, float *v, float *f);
    void freeParticle(struct Particle *p);
    void printParticle(struct Particle *p);

// ParticleSystem
 public:
    static struct ParticleSystem *createParticleSystem(int numberOfParticles);
    void freeParticleSystem(struct ParticleSystem *p);
    void printParticleSystem(struct ParticleSystem *p);
    static float *particlePositions(struct ParticleSystem *p);
};

#endif  // PARTICLEFACTORY_H

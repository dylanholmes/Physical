#ifndef SYSTEM_H
#define SYSTEM_H

#include <assert.h>
#include <iostream>

#include "Particle.h"

#include "UnaryForce.h"
#include "DampedSpringForce.h"

class System {
 public:
    System();

// Solver interface
 public:
    ParticleSystem *getParticleSystem();
    void setParticleSystem(ParticleSystem *p);
    bool addForce(Force *f);
    void eulerStep(float deltaT);

 private:
    void clearForces();
    void calculateForces();
    // length of state derivative and force vectors
    int particleDimensions();
    // gather state from particles into dst
    void getParticleState(float *dst);
    // scatter state from src to particles
    void setParticleState(float *src);
    // calculate derivative, place in dst
    void particleDerivative(float *dst);

    void addVectors(float *v, float *u, float *r);
    void scaleVector(float *v, float a);

// P

 private:
    ParticleSystem *p;
    float *temp1;
    float *temp2;

    
};

#endif  // SYSTEM_H

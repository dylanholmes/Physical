#ifndef SYSTEMFACTORY_H
#define SYSTEMFACTORY_H

#include "System.h"
#include "Particle.h"
#include "ParticleFactory.h"

#include "DampedSpringForce.h"
#include "InverseSquareForce.h"
#include "UnaryForce.h"

class SystemFactory {
 public:
    static System setupFor2();
    static System setupFor100();
    static System setupForSpringBox(float s, float ks, float kd, float r);
    static System setupForFoldedSpringChain(int s, float space,  float ks, float kd, float r);

};

#endif  // SYSTEMFACTORY_H

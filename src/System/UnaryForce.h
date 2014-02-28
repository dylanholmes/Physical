#ifndef UNARYFORCE_H
#define UNARYFORCE_H

#include <iostream>
#include "Particle.h"
#include "Force.h"

class UnaryForce : public Force {

 public:
    UnaryForce(struct Particle **p, int n, float f[3]);

 public:
    void applyForce();

 private:
    struct Particle **p;
    int n;
    float f[3];
    
};

#endif  // UNARYFORCE_H

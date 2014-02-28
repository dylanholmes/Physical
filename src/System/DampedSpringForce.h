#ifndef DAMPEDSPRINGFORCE_H
#define DAMPEDSPRINGFORCE_H

#include <cmath>  // only for sqrt
#include <iostream>
#include "Particle.h"
#include "Force.h"

// TODO:
//   + Array of parameters for each pair of particles


class DampedSpringForce : public Force {
 public:
    DampedSpringForce(struct Particle **p, int n, float ks, float kd, float r);

 public:
    void applyForce();

 private:
    struct Particle **p;
    int n;
    float ks;
    float kd;
    float r;
};

#endif  // DAMPEDSPRINGFORCE_H

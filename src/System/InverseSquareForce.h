#ifndef INVERSESQUAREFORCE_H
#define INVERSESQUAREFORCE_H

#include "math.h"
#include <iostream>
#include "Particle.h"
#include "Force.h"

class InverseSquareForce : public Force {
public:
    InverseSquareForce(struct Particle **p, int n, float k);

 public:
    void applyForce();

 private:
    struct Particle **p;
    int n;
    float k;
};

#endif  // INVERSESQUAREFORCE_H
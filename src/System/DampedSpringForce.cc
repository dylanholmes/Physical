#include "DampedSpringForce.h"

DampedSpringForce::DampedSpringForce( struct Particle **p, int n, float ks,
	float kd, float r) {
    this->p = p;
    this->n = n;

    this->ks = ks;
    this->kd = kd, 
    this->r = r;
}

void DampedSpringForce::applyForce() {
    const int dim = 3;
    float deltaX[dim];
    float deltaV[dim];
    float d;
    float deltaXDotdeltaV;
    float a;
    float f[dim];

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            // f1 = -( ks * (d - r) + kd * ( deltaXDotdeltaV / d) ) deltaX/ d;
            
            subtractVectors(p[i]->x, p[j]->x, deltaX, dim); // x1 - x2
            subtractVectors(p[i]->v, p[j]->v, deltaV, dim); // x1 - x2
            d = sqrt(dotVectors(deltaX, deltaX, dim));
            deltaXDotdeltaV = dotVectors(deltaX, deltaV, dim);
        
            // Calculate force of p2 on p1 (applied to p1)
            a = -( ks * (d - r) + kd * ( deltaXDotdeltaV / d) ) / d;
            memset(f, 0, sizeof(f)); // f allocated automatically

            addVectors(deltaX, f,  f, dim);
            scaleVector(f, a, dim);
        
            // Apply force on p1
            addVectors(p[i]->f, f,  p[i]->f, dim);
        
            // Apply force on p2 (f1 = -f2 <==> Newtons 3rd law!)
            scaleVector(f, -1, dim);
            addVectors(p[j]->f, f,  p[j]->f, dim);
        }
    }
}

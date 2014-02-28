#include "UnaryForce.h"

UnaryForce::UnaryForce(struct Particle **p, int n, float f[3]) {
    this->p = p;
    this->n = n;
    memcpy(this->f, f, 3 * sizeof(float));
}

void UnaryForce::applyForce() {
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < 3; j++)
            p[i]->x[j] += f[j];
}

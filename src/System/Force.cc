#include "Force.h"

float Force::dotVectors(float *v, float *u, int dim) {
    float dot = 0;
    int i;
    for (i = 0; i < dim; i++)
        dot += *(v++) * *(u++);

    return dot;
}

void Force::addVectors(float *v, float *u, float *r, int dim) {
    int i;
    for (i = 0; i < dim; i++)
        *(r++) = *(v++) + *(u++);
}

void Force::subtractVectors(float *v, float *u, float *r, int dim) {
    int i;
    for (i = 0; i < dim; i++)
        *(r++) = *(v++) - *(u++);
}

void Force::scaleVector(float *v, float a, int dim) {
    int i;
    for (i = 0; i < dim; i++)
        *(v++) *= a;
}
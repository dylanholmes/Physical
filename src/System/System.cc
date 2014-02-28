#include "System.h"

System::System() {
    p = NULL;
}

ParticleSystem *System::getParticleSystem() {
    if (p != NULL)
        return p;
    return 0;
}

bool System::addForce(Force *f) {
    if (p == NULL)
        return false;

    if (p->F == NULL)
        p->F = (Force **)malloc(sizeof(Force *));
    else
        p->F = (Force **)realloc(p->F, sizeof(Force *)*(p->nF + 1));

    assert(p->F != NULL);

    p->F[p->nF] = f;
    p->nF++;
    return true;
}

void System::setParticleSystem(ParticleSystem *p) {
    this->p = p;

    // create copies for eulerstep
    temp1 = (float *)malloc(sizeof(float)*particleDimensions());
    temp2 = (float *)malloc(sizeof(float)*particleDimensions());
}

void System::eulerStep(float deltaT) {
    // get deriv
    particleDerivative(temp1);
    // scale it
    scaleVector(temp1, deltaT);
    // get state
    getParticleState(temp2);
    // add -> temp2
    addVectors(temp1, temp2, temp2);
    // update state
    setParticleState(temp2);
    // update time
    p->t = deltaT;
}

// Solver interface
void System::clearForces() {
    int i, j;
    for (i = 0; i < p->n; i++)
        for (j = 0; j < 3; j++)
            p->p[i]->f[j] = 0;
}

void System::calculateForces() {
    int i;
    for (i = 0; i < p->nF; i++)
            p->F[i]->applyForce();
}
    // length of state derivative and force vectors
int System::particleDimensions() {
    return (6 * p->n);
}
    // gather state from particles into dst
void System::getParticleState(float *dst) {
    int i, j;
    for (i = 0; i < p->n; i++) {
        for (j = 0; j < 3; j++)
            *(dst++) = p->p[i]->x[j];
        for (j = 0; j < 3; j++)
            *(dst++) = p->p[i]->v[j];
    }
}
    // scatter state from src to particles
void System::setParticleState(float *src) {
    int i, j;
    for (i = 0; i < p->n; i++) {
        for (j = 0; j < 3; j++)
            p->p[i]->x[j] = *(src++);
        for (j = 0; j < 3; j++)
            p->p[i]->v[j] = *(src++);
    }
}
    // calculate derivative, place in dst
void System::particleDerivative(float *dst) {
    int i, j;
    clearForces();  // zero the accumulator
    calculateForces();  // magic force function
    for (i = 0; i < p->n; i++) {
        for (j = 0; j < 3; j++)
            *(dst++) = p->p[i]->v[j];
        for (j = 0; j < 3; j++)
            *(dst++) = p->p[i]->f[j] / p->p[i]->m;
    }
}

void System::addVectors(float *v, float *u, float *r) {
    int i;
    for (i = 0; i < particleDimensions(); i++)
        *(r++) = *(v++) + *(u++);
}

void System::scaleVector(float *v, float a) {
    int i;
    for (i = 0; i < particleDimensions(); i++)
        *(v++) *= a;
}

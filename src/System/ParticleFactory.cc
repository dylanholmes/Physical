#include "ParticleFactory.h"

// Particle

struct Particle *ParticleFactory::createParticle(float m, float x[3], float v[3], float f[3]) {
    struct Particle *p = (Particle *)malloc(sizeof(struct Particle));
    assert(p != NULL);

    p->m = m;
    int i;
    for (i = 0; i < 3; i++) {
        p->x[i] = x[i];
        p->v[i] = v[i];
        p->f[i] = f[i];
    }

    return p;
}

void ParticleFactory::freeParticle(struct Particle *p) {
    assert(p != NULL);

    free(p->x);
    free(p->v);
    free(p->f);
    free(p);
}

void ParticleFactory::printParticle(struct Particle *p) {
    std::cout << p->m << std::endl;
    int i;
    for (i = 0; i < 3; i++) {
        std::cout << p->x[i] << std::endl;
        std::cout << p->v[i] << std::endl;
        std::cout << p->f[i] << std::endl;
    }
}

// ParticleSystem

struct ParticleSystem *ParticleFactory::createParticleSystem(int numberOfParticles) {
    struct ParticleSystem *ps = (ParticleSystem *)malloc(sizeof(struct ParticleSystem));;
    assert(ps != NULL);

    // ParticleSystem->Particles
    
    Particle **p = (Particle **)malloc(sizeof(*p)*numberOfParticles);
    assert(p != NULL);
    int i;
    for (i = 0; i < numberOfParticles; i++) {
        float m = 1; // m > 0
        float x[3] = {0};
        float v[3] = {0};
        float f[3] = {0};
        p[i] = createParticle(m, x, v, f);
    }

    // Assign
    ps->p = p;
    ps->n = numberOfParticles;
    ps->t = 0;
    ps->F = NULL;
    ps->nF = 0;
    return ps;
}
    void ParticleFactory::freeParticleSystem(struct ParticleSystem *p)
 {

 }
    void ParticleFactory::printParticleSystem(struct ParticleSystem *p)
 {

 }

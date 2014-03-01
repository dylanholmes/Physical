#include "ParticleSystem.h"

ParticleSystem::ParticleSystem() {
    this->time = 0;
}

ParticleSystem::addParticle(Particle p);
ParticleSystem::addParticles(std::vector<Particle> p);
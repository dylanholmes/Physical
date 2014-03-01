#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include <vector>
#include "Particle.h"

// forward declarations
class Force;

class ParticleSystem {
 public:
    explicit ParticleSystem(std::vector<Particle> p);

 public:
    addParticle(Particle p);
    addParticles(std::vector<Particle> p);

 private:
    std::vector<Particle> particles;
    std::vector<Force> forces;
    float time;  // simulation clock
};

#endif  // PARTICLESYSTEM_H

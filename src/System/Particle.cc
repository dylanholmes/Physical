#include "Particle.h"


Particle::Particle(float m = 0, std::vector<float> x(3, 0), std::vector<float> v(3, 0),
    std::vector<float> f(3, 0)) {
    this->mass = m;
    this->position = x;
    this->velocity = v;
    this->force = f;
}

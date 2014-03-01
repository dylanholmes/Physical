#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

// forward declarations
class Force;

class Particle {
 public:
  Particle(float m = 0, std::vector<float> x(3, 0), std::vector<float> v(3, 0),
    std::vector<float> f(3, 0));

 private:
    float mass;
    std::vector<float> position(3, 0);
    std::vector<float> velocity(3, 0);
    std::vector<float> force(3, 0);
};

#endif  // PARTICLE_H

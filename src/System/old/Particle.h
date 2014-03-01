#ifndef PARTICLE_H
#define PARTICLE_H

// forward declarations
class Force;

class Particle {
 public:
 	Particle();
 	Particle(float m, float (&x)[3], float (&x)[3], float (&f)[3]);

 private:
	float m;
	float x[3];
	float v[3];
	float f[3];
};

struct Particle {
    float m;  // mass
    float x[3];  // position vector
    float v[3];  // velocity vector
    float f[3];  // force accumulator
};


struct ParticleSystem {
    Particle **p;  // array of pointers to particles
    int n;  // number of particles
    float t;  // simulation clock
    Force **F;  // array of pointers to force objects
    int nF;  // number of Force objects
};

#endif  // PARTICLE_H

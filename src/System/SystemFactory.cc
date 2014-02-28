#include "SystemFactory.h"

System SystemFactory::setupFor2() {
  System system;
  int i;
  const int kNumberOfParticles = 2;
  float positions[kNumberOfParticles*3];

  ParticleSystem *ps = ParticleFactory::createParticleSystem(
    kNumberOfParticles);
  system.setParticleSystem(ps);

  system.addForce(new InverseSquareForce(ps->p, ps->n, -100));

  // IC's
  ps->p[0]->m = 100;
  ps->p[0]->x[0] = 0;
  ps->p[0]->x[1] = 0;
  ps->p[0]->v[0] = 0;
  ps->p[0]->v[1] = 0;

  ps->p[1]->m = 1;
  ps->p[1]->x[0] = 0.3;
  ps->p[1]->x[1] = 0;
  ps->p[1]->v[0] = 0;
  ps->p[1]->v[1] = 5;

  return system;
}

System SystemFactory::setupFor100() {
  System system;
  int i;
  const int kNumberOfParticles = 100;
  float positions[kNumberOfParticles*3];

  ParticleSystem *ps = ParticleFactory::createParticleSystem(
    kNumberOfParticles);
  system.setParticleSystem(ps);

  system.addForce(new DampedSpringForce(ps->p, ps->n, 100, 0.01, 0.4));

  // grid
  int rows = 10;
  int cols =10;
  float colspace = 0.1;
  float rowspace = 0.1;
  for (i = 0; i < ps->n; i++) {
    ps->p[i]->x[0] = -colspace*cols/2.0 + (i % cols)*colspace;
    ps->p[i]->x[1] = -rowspace*rows/2.0 + (i / rows)*rowspace;
  }

  return system;
}

System setupForSpringBox(float s, float ks, float kd, float r) {
  System system;
  int i;
  const int kNumberOfParticles = s*s;
  float positions[kNumberOfParticles*3];

  ParticleSystem *ps = ParticleFactory::createParticleSystem(
    kNumberOfParticles);
  system.setParticleSystem(ps);

  int rows = s;
  int cols = s;
  Particle **pair;
  for (i = 0; i < ps->n -1; i++) {
    pair = (Particle **)malloc(sizeof(*pair)*2);
    if ( i % cols != cols-1 ) {
      pair[0] = ps->p[i];
      pair[1] = ps->p[i+1];
      system.addForce(new DampedSpringForce(pair, 2, ks, kd, r));
    }
    pair = (Particle **)malloc(sizeof(*pair)*2);
    if (i/cols != rows-1) {
      pair[0] = ps->p[i];
      pair[1] = ps->p[i + cols];
      system.addForce(new DampedSpringForce(pair, 2, ks, kd, r));
    }
  }

  // grid
  float colspace = 0.1;
  float rowspace = 0.1;
  for (i = 0; i < ps->n; i++) {
    ps->p[i]->x[0] = -colspace*cols/2.0 + (i % cols)*colspace;
    ps->p[i]->x[1] = -rowspace*rows/2.0 + (i / cols)*rowspace;
  }

  // make it pop
  float g[3] = {0, 0.0001, 0};
  system.addForce(new UnaryForce(ps->p, ps->n, g));

  return system;
}

System SystemFactory::setupForFoldedSpringChain(int s, float space,  float ks,
    float kd, float r) {
  System system;
  int i;
  const int kNumberOfParticles = s*s;
  float positions[kNumberOfParticles*3];

  ParticleSystem *ps = ParticleFactory::createParticleSystem(
    kNumberOfParticles);
  system.setParticleSystem(ps);

  int rows = s;
  int cols = s;
  Particle **pair;
  for (i = 0; i < ps->n -1; i++) {
    pair = (Particle **)malloc(sizeof(*pair)*2);
    if ( i % cols != cols-1 ) {
      pair[0] = ps->p[i];
      pair[1] = ps->p[i+1];
      system.addForce(new DampedSpringForce(pair, 2, ks, kd, r));
    }
    pair = (Particle **)malloc(sizeof(*pair)*2);
    if (i%cols == cols-1  // last colum
      && !((i / cols) % 2 )  // odd row
      && (i/cols != (ps->n-1)/cols)) {  // not last row
      pair[0] = ps->p[i];
      pair[1] = ps->p[i + cols];
      system.addForce(new DampedSpringForce(pair, 2, ks, kd, r));
    }
    if (i%cols == 0  // first column
      && ((i / cols) % 2)  // even row
      && i/cols != 0  // not first row
      && (i/cols != (ps->n-1)/cols)) {  // not last row
      pair[0] = ps->p[i];
      pair[1] = ps->p[i + cols];
      system.addForce(new DampedSpringForce(pair, 2, ks, kd, r));
    }
  }

  // grid
  float colspace = space;
  float rowspace = space;
  for (i = 0; i < ps->n; i++) {
    ps->p[i]->x[0] = -colspace*cols/2.0 + (i % cols)*colspace;
    ps->p[i]->x[1] = -rowspace*rows/2.0 + (i / cols)*rowspace;
  }

  // make it pop
  float g[3] = {0, -0.001, 0};
  system.addForce(new UnaryForce(ps->p, ps->n, g));

  return system;
}

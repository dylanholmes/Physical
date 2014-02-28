#ifndef FORCE_H
#define FORCE_H

class Force {
 public:
    virtual void applyForce() = 0;  // pure virtual function

 protected:
    float dotVectors(float *v, float *u, int dim);
    void addVectors(float *v, float *u, float *r, int dim);
    void subtractVectors(float *v, float *u, float *r, int dim);
    void scaleVector(float *v, float a, int dim);

};

#endif  // FORCE_H
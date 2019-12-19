#ifndef PARTICLE_H
#define PARTICLE_H
#include <Vector.h>
#include <list>

#define EPSILON 0.00001

using mtools::Vector_f;
using std::list;
class Particle:public Vector_f
{
public:
  Particle():Vector_f(){
      COSPIOVER6TIME2 = 0.5777350269189625;
      lambda = 0.001;
      energy = 0.0;
      b_idx = 0;
  }
  Particle(float _x, float _y, float _z):
      Vector_f(_x,_y,_z){
      COSPIOVER6TIME2 = 0.5777350269189625;
      lambda = 0.001;
      energy = 1e6;
      b_idx = 0;
  }
  Particle(Vector_f &v):Vector_f(v){
      COSPIOVER6TIME2 = 0.5777350269189625;
      lambda = 0.001;
      energy = 1e6;
      b_idx = 0;
  }
  Particle(const Particle &p){
      COSPIOVER6TIME2 = 0.5777350269189625;
      x = p.x;
      y = p.y;
      z = p.z;
      lambda = p.lambda;
      energy = p.energy;
      b_idx = p.b_idx;
      biter = p.biter;
      niter = p.niter;
  }
  Particle& operator=(const Vector_f &v){
      Vector_f::operator=(v);
      COSPIOVER6TIME2 = 0.5777350269189625;
      lambda = 0.001;
      energy = 1e6;
      b_idx = 0;
  }

  Vector_f dist(Vector_f &n);
  float calcLfs();
  float calcSizingField();
  float partial_der_energy_radius, energy;
  float COSPIOVER6TIME2, lambda;
  list<Particle*>::iterator biter,niter;
  int b_idx;
  float d,density;
  const static float r;
  float lfs;

};

#endif // PARTICLE_H

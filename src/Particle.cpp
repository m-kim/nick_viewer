#include "Particle.h"

const float Particle::r = 1.0;

Vector_f Particle::dist(Vector_f &n)
{
   //temporary set sf to 1.0
    lfs = calcSizingField();
    float alpha = 1.0 * lfs;//min(p.sf, n.sf);
    Vector_f len = *this;
    len -= n;
    len *= COSPIOVER6TIME2/(EPSILON + alpha);
    return len;
}

float Particle::calcLfs()
{
    //distance to medial access
    //temporarily a sphere
    static Vector_f sph = Vector_f(9,9,9);
    static float rad = 3.0;
    float dist = (*this - sph).length() / rad;
    if (dist < 1.0){
        return  dist;
    }
    else{
        return 1.0;
    }
}

float Particle::calcSizingField()
{
    static Vector_f sph = Vector_f(9,9,9);
    static float rad = 3.0;
    static float epsilon = 0.5;
    static float C = epsilon * 2.0;
    float dist = calcLfs();
    dist = C*fmin(dist, 1.0/dist);

    return 1.0;
}

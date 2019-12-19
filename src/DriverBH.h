#ifndef DRIVERBH_H
#define DRIVERBH_H
#include "Particle.h"
#include <vector>
#include <sstream>

using std::stringstream;
using std::vector;
class BarnesHut;
class DriverBH
{
public:
    DriverBH();
    ~DriverBH();
    void saveParticles(stringstream &fn);


    BarnesHut *bh;
    vector<Particle> prts;

    float unit_length;
};

#endif // DRIVERBH_H

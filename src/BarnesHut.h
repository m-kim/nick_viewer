#ifndef BARNESHUT_H
#define BARNESHUT_H
#include "BHNode.h"
#include "BBox.h"
#include "Particle.h"
#include <vector>
#include "Vector.h"

using std::vector;
class BarnesHut
{
public:
    BarnesHut(vector<Particle> &, mtools::Vector<int>, int _depth = 1000, float theta = 1.1);
    ~BarnesHut();
    void deleteTree();
    BHNode *deleteNode(BHNode *);
    void buildTree();
    void makeNode();
    void addBody(BHNode*, int, int);
    int getOct(int, BBox);
    void makeNode(BHNode *parent, int oct, int);
    void doTree( int bI);
    void doTreeRecurse(int bI, BHNode *node);
    void setAccel(int, int);
    Vector_f calcForce(float m1, Particle &v1, float m2, Vector_f &v2);
    void setAccelLeafToNode(int i,float m,Vector_f &p);
    void calcForces();
    void run(int start, int end);
    BHNode *root;
    const int MAXDEPTH;
    const float BN_THETA;
    vector<Vector_f> reps;
    vector<Particle> prts;
    int num_checks;
    int max_depth;
private:
    const static float mass;

};

#endif // BARNESHUT_H

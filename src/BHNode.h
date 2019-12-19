#ifndef BHNODE_H
#define BHNODE_H
#include <Vector.h>
#include <vector>
#include <limits>
#include "BBox.h"


using mtools::Vector_f;

class BHNode
{
public:
    BHNode();
    ~BHNode();
    bool leaf;
    float mass;
    Vector_f center;
    BHNode *nodes[8];
    BBox box;
    std::vector<int> body;
};

#endif // BHNODE_H

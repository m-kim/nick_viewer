#include "BarnesHut.h"
#include "BHNode.h"

#include <vector>
#include <algorithm>

using std::vector;
using mtools::Vector;

const float BarnesHut::mass = 1e5;

BarnesHut::BarnesHut(vector<Particle> &_p, Vector<int> d, int _depth , float theta):
    MAXDEPTH(_depth),
    BN_THETA(theta)

{
    root = 0;
    prts = _p;
    reps.resize(prts.size());

    max_depth = 0;
}
BarnesHut::~BarnesHut()
{
    deleteTree();
}

void BarnesHut::buildTree()
{
    deleteTree();
    root = new BHNode();
    root->box.setMin(0.0);
    root->box.setMax(1);
    for (int i=0; i<prts.size(); i++){
        if (root->box.inside(prts[i])){
            addBody(root,i,0);
        }
    }
}

void BarnesHut::deleteTree()
{
    if (root) {
        root = deleteNode(root);
    }
}

BHNode *BarnesHut::deleteNode(BHNode *node)
{
    node->body.clear();
    node->box.reset();
    // For each child
    for (int i=0;i<8;i++) {
        if (node->nodes[i]) { // If child exists
            node->nodes[i] = deleteNode(node->nodes[i]);
        }
    }
    delete node;
    return 0;
}

int BarnesHut::getOct( int i, BBox box)
{
    Vector_f mid = box.getMax() - box.getMin();
    mid /= 2;
    mid += box.getMin();

   if (prts[i].z < mid.z){
        if (prts[i].y < mid.y){
            if (prts[i].x < mid.x){
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            if (prts[i].x < mid.x){
                return 2;
            }
            else{
                return 3;
            }
        }
    }
    else{
        if (prts[i].y < mid.y){
            if (prts[i].x < mid.x){
                return 4;
            }
            else{
                return 5;
            }
        }
        else{
            if (prts[i].x < mid.x){
                return 6;
            }
            else{
                return 7;
            }
        }
    }
}

void BarnesHut::addBody(BHNode *node, int i, int depth)
{
    if (node->body.size() > 0){
        if (depth > MAXDEPTH){
            node->body.push_back(i);
        }

        else{
            vector<int> subBodies;
            if (!node->leaf){
                subBodies.push_back(i);
            }
            else{
                subBodies.push_back(i);
                for (int j=0; j<node->body.size(); j++){
                    subBodies.push_back(node->body[j]);
                }
            }
            for (int k=0; k<subBodies.size(); k++){
                int oct = getOct(subBodies[k], node->box);
                BHNode *child = node->nodes[oct];
                if (child){
                    addBody(child, subBodies[k], depth+1);
                }
                else{
                    makeNode(node, oct, subBodies[k]);
                    if (max_depth < depth)
                        max_depth = depth;
                }
            }
            node->leaf = 0;
        }
        node->center = (node->center*node->mass + prts[i]*mass)/(node->mass + mass);
        node->mass += mass;
    }
    else{
        node->body.push_back(i);
        // Center of Mass set to the position of single body
        node->center = prts[i];
        node->mass = mass;
    }
}

void BarnesHut::makeNode(BHNode *parent, int oct, int child_idx)
{
    BHNode *new_child = new BHNode();
    new_child->body.push_back(child_idx);
    new_child->center = prts[child_idx];
    new_child->mass = mass;

    Vector_f _min, _max, mid = parent->box.getMax() - parent->box.getMin();
    mid /= 2;
    mid += parent->box.getMin();

    switch(oct){
    case 0://near, lower, left
        _min = parent->box.getMin();
        _max = mid;
        break;
    case 1://near, lower, right
        _min = parent->box.getMin();
        _max = mid;
        _min.x = mid.x;
        _max.x = parent->box.getMax().x;
        break;
    case 2://near, upper, left
        _min = parent->box.getMin();
        _max = mid;
        _min.y = mid.y;
        _max.y = parent->box.getMax().y;
        break;
    case 3://near, upper, right
        _min = mid;
        _max = parent->box.getMax();
        _min.z = parent->box.getMin().z;
        _max.z = mid.z;
        break;
    case 4://far, lower, left
        _min = parent->box.getMin();
        _max = mid;
        _min.z = mid.z;
        _max.z = parent->box.getMax().z;
        break;
    case 5://far, lower, right
        _min = parent->box.getMin();
        _max = mid;
        _min.x = mid.x;
        _max.x = parent->box.getMax().x;
        _min.z = mid.z;
        _max.z = parent->box.getMax().z;
        break;
    case 6://far, upper, left
        _min = parent->box.getMin();
        _max = mid;
        _min.y = mid.y;
        _max.y = parent->box.getMax().y;
        _min.z = mid.z;
        _max.z = parent->box.getMax().z;
        break;
    case 7://far, upper, right
        _min = mid;
        _max = parent->box.getMax();
        break;

    }
    new_child->box.setMin(_min);
    new_child->box.setMax(_max);

    parent->nodes[oct] = new_child;
}

void BarnesHut::doTree(int bI) {
    doTreeRecurse(bI,root);
}


void BarnesHut::doTreeRecurse(int bI, BHNode *node) {
    if (node->leaf) {
        for (int k=0;k<node->body.size();k++) {
            if (bI != node->body[k]) {
                setAccel(bI,node->body[k]);
                num_checks ++;
            }
        }
    }
    else {
        Vector_f len = node->box.getMax() - node->box.getMin();

        float s = std::min( (float)fabs(len.x), (float)fabs(len.y) );
        s = std::min(s, (float)fabs(len.z));
        float d = (prts[bI] - node->center).length();
        float delta = s/d;
        if (delta < BN_THETA) {
            setAccelLeafToNode(bI,node->mass,node->center);
            num_checks ++;
        }
        else {
            for (int k=0;k<8;k++) {
                if (node->nodes[k]) {
                    doTreeRecurse(bI,node->nodes[k]);
                }
            }
        }
    }
}

void BarnesHut::setAccel(int i, int j) {

    Vector_f F = calcForce(mass, prts[i],mass, prts[j]);

    // a = F/m
    reps[i] += F;///mass;

}
void BarnesHut::setAccelLeafToNode(int i,float m,Vector_f &p)
{
    // get Force Vector between particle i
    // and a virtual mass, m
    //   with mass m, at position cx,cy
    Vector_f F = calcForce(
        m,prts[i],mass , p);

    reps[i] += F;//mass;
}


Vector_f BarnesHut::calcForce(float m1, Particle &v1, float m2, Vector_f &v2) {
//    float r = v1.dist(v2).length();
//    if (r < 1.0){
//        Vector_f norm = (v1-v2);
//        norm /= (EPSILON + norm.length());
//        float tmp = 1.0 /(EPSILON + sin(r * M_PI * .5));
//        float ret = (1 - tmp * tmp) * M_PI * .5;
//        return norm * ret;
//    }
//    else
//        return Vector_f(0.0,0.0,0.0);
    const static float ETA = 0.0;
    const static float DISTANCE_MULTIPLE = 1.3;
    const static float G = 6.67384e-11;
    const static float GFACTOR = 3.0;
    Vector_f dx = v1 - v2;
    float r = (dx.length()+ETA) * DISTANCE_MULTIPLE;
    float F = G*m1*m2/(EPSILON + pow(r,GFACTOR));
    return dx*F/(EPSILON + r);
}

void BarnesHut::calcForces() {
    buildTree();
    num_checks = 0;
    for (int i=0;i<prts.size();i++) {
        doTree(i);
    }
}

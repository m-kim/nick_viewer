#ifndef DRAWBH_H
#define DRAWBH_H
#include "../src/BBox.h"

class DriverBH;
class BHNode;

class DrawBH
{
public:
    DrawBH();
    void drawRoot(DriverBH *);
    void drawLevel(DriverBH *);
    void drawObject(DriverBH *);
    int level;
    bool stop_at_leaf;
private:
    void drawLevel(BHNode *, int);
    void drawPoints(BHNode *node);
    void drawBox(const BBox &box);

};

#endif // DRAWBH_H


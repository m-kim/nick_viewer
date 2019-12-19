#include "drawbh.h"
#include <GL/glew.h>
#include <iostream>

#include "../src/DriverBH.h"
#include "../src/BarnesHut.h"
#include "../src/BHNode.h"


using namespace std;

DrawBH::DrawBH()
{
    level = 0;
    stop_at_leaf = 0;
}


void DrawBH::drawRoot(DriverBH *drv)
{
    drawBox(drv->bh->root->box);
}

void DrawBH::drawBox(const BBox &box)
{
    glBegin(GL_LINE_LOOP);
    glVertex3f(box.getMin().x,   box.getMin().y,  box.getMin().z);
    glVertex3f(box.getMax().x,   box.getMin().y,  box.getMin().z);
    glVertex3f(box.getMax().x,   box.getMax().y,  box.getMin().z);
    glVertex3f(box.getMin().x,   box.getMax().y,  box.getMin().z);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex3f(box.getMin().x,   box.getMin().y,  box.getMax().z);
    glVertex3f(box.getMax().x,   box.getMin().y,  box.getMax().z);
    glVertex3f(box.getMax().x,   box.getMax().y,  box.getMax().z);
    glVertex3f(box.getMin().x,   box.getMax().y,  box.getMax().z);
    glEnd();

    glBegin(GL_LINES);
    glVertex3f(box.getMax().x,  box.getMin().y, box.getMin().z);
    glVertex3f(box.getMax().x,  box.getMin().y, box.getMax().z);
    glVertex3f(box.getMin().x,  box.getMin().y, box.getMin().z);
    glVertex3f(box.getMin().x,  box.getMin().y, box.getMax().z);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(box.getMax().x,  box.getMax().y, box.getMin().z);
    glVertex3f(box.getMax().x,  box.getMax().y, box.getMax().z);
    glVertex3f(box.getMin().x,  box.getMax().y, box.getMin().z);
    glVertex3f(box.getMin().x,  box.getMax().y, box.getMax().z);
    glEnd();
}

void DrawBH::drawPoints(BHNode *node)
{
    if (node->leaf) {
        glBegin(GL_POINTS);
        glVertex3f(node->center.x, node->center.y, node->center.z);
        glEnd();
    }
    else{
        for (int k=0;k<8;k++) {
            if (node->nodes[k]) {
                drawPoints(node->nodes[k]);
            }
        }
    }
}

void DrawBH::drawLevel(BHNode *node, int rlevel)
{
    if ( (stop_at_leaf&&(node->leaf == true)) || rlevel < 2){
        drawBox(node->box);
        drawPoints(node);
    }
//    if (rlevel < 2){
//        for (int k=0;k<8;k++) {
//            if (node->nodes[k]) {
//                drawBox(node->nodes[k]->box);
//                drawPoints(node);
//            }
//        }
//    }
    else{
        for (int k=0;k<8;k++) {
            if (node->nodes[k]) {
                drawLevel(node->nodes[k], rlevel-1);
            }
        }
    }
}

void DrawBH::drawLevel(DriverBH *drv)
{
    drawRoot(drv);
    if (level > 0)
        drawLevel(drv->bh->root, std::min(level, drv->bh->max_depth));

}

void DrawBH::drawObject(DriverBH *drv)
{
    glBegin(GL_POINTS);
    for (int i=0; i<drv->prts.size(); i++){
        //if ( (drv->prts[i] - ctr).length() < rad){
        glVertex3f(drv->prts[i].x, drv->prts[i].y, drv->prts[i].z);
    }

//    for (int i=0; i<drv->bins.size(); i++){
//        list<Particle*>::iterator it;
//        for (it=drv->bins[i].begin(); it != drv->bins[i].end(); it++){
//            glVertex3f((*it)->x, (*it)->y, (*it)->z);
//        }
//    }
    glEnd();
}

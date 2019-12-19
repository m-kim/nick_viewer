#include "BBox.h"

#include <limits>

using mtools::Vector_f;
BBox::BBox()
{
    empty = 1;
}

BBox::~BBox()
{

}

void BBox::setMin(Vector_f _m)
{
    min = _m;
    isEmpty();
}

void BBox::setMin(float _m)
{
    min = Vector_f(_m,_m,_m);
    isEmpty();
}

void BBox::setMax(Vector_f _m)
{
    max = _m;
    isEmpty();
}

void BBox::setMax(float _m)
{
    max = Vector_f(_m,_m,_m);
    isEmpty();
}

void BBox::reset()
{
    min = mtools::Vector_f(std::numeric_limits<float>::max());
    max = mtools::Vector_f(std::numeric_limits<float>::min());
    isEmpty();
}

bool BBox::isEmpty()
{
    empty = !(min.x < max.x && min.y < max.y && min.z < max.z);
    return empty;
}

bool BBox::inside(const Vector_f &pos)
{
    return (pos.x > min.x && pos.x < max.x &&
            pos.y > min.y && pos.y < max.y &&
            pos.z > min.z && pos.z < max.z);
}

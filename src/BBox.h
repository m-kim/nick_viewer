#ifndef BBOX_H
#define BBOX_H
#include <Vector.h>

using mtools::Vector_f;
class BBox
{
public:
    BBox();
    ~BBox();
    Vector_f getMin() const {return min;};
    Vector_f getMax() const {return max;};

    void setMin(Vector_f _m);
    void setMin(float _m);
    void setMax(Vector_f _m);
    void setMax(float _m);
    void reset();
    bool isEmpty();
    bool inside(const Vector_f &pos);
private:
    Vector_f min, max;
    bool empty;
};
#endif // BBOX_H

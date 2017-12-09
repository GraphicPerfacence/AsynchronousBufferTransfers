#ifndef _OPENGL_Geometry_H
#define _OPENGL_Geometry_H

#include "base.hpp"
#include "geometry/AABB.hpp"
#include "RefPointer.hpp"

class Geometry: public Base
{
public:

    typedef AABox<float>    AABox;
    typedef Vector3<float>  V3;

    Geometry();

    ~Geometry();

    virtual void            Draw() = 0;
    virtual void            DrawGeometry()const = 0;

    virtual const AABox&    GetBoundingBox()const = 0;
    virtual const unsigned  TriangleCount() const = 0;

};

typedef RefPointer<Geometry>    RefGeometry;

#endif
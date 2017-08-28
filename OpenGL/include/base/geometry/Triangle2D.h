#ifndef _OPENGL_Triangle2D_H
#define _OPENGL_Triangle2D_H

    //---------------------------------------------------------------------------
#include "../defType.hpp"
#include "../../math/const.h"
    //---------------------------------------------------------------------------

template<class REAL>
struct Triangle2D
{
    typedef Vector2<REAL> V2;

    V2 a,b,c;

    Triangle2D(const V2& vA, const V2& vB, const V2& vC):
    a(vA), b(vB), c(vC) { }

    const bool Contains(const V2& p) const
    {
    const REAL eps = Const<REAL>::epsilon();
    const REAL eps1 = REAL(1.0)+eps;
    const REAL epsNeg = -eps;

        //solved with barycentric coordinates
    const REAL denom = (b.x()-a.x())*(c.y()-a.y())-(c.x()-a.x())*(b.y()-a.y());

    if(0 == denom)
        { // no division by 0
            return false;
        }

    REAL uvw = ((b.x()-p.x())*(c.y()-p.y())-(c.x()-p.x())*(b.y()-p.y()))/denom; //u

    if((uvw < epsNeg) || (eps1 < uvw))
        {
        return false;
        }

    uvw = ((c.x()-p.x())*(a.y()-p.y())-(a.x()-p.x())*(c.y()-p.y()))/denom; //v

    if((uvw < epsNeg) || (eps1 < uvw))
        {
        return false;
        }

    uvw = ((a.x()-p.x())*(b.y()-p.y())-(b.x()-p.x())*(a.y()-p.y()))/denom; //w
    if((uvw < epsNeg) || (eps1 < uvw))
        {
        return false;
        }
    
    return true;
    }
};


#endif

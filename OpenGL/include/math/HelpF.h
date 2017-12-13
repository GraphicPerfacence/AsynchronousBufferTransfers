    //
    //  Header.h
    //  openGLTest
    //
    //  Created by xt on 17/8/28.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#ifndef OPENGL_M_HEAD_H
#define OPENGL_M_HEAD_H

#include "base/defType.hpp"
#include "math/const.h"


namespace math
{
    template<class REAL>
    bool clipTest(const REAL& p, const REAL& q, REAL& u1, REAL& u2)
    {
    if(p < 0.0)
        {
        const REAL r = q/p;
        if(r > u2)
            {
            return false;
            }
        else
            {
            if(r > u1)
                {
                u1 = r;
                }
            return true;
            }
        }
    else
        {
        if(p > 0.0)
            {
            const REAL r = q/p;
            if(r < u1)
                {
                return false;
                }
            else
                {
                if(r < u2)
                    {
                    u2 = r;
                    }
                return true;
                }
            }
        else
            {
            return q >= 0.0;
            }
        }
    }


    template <class REAL>
    inline Vector3<REAL> normal(Vector3<REAL> v)
    {
    return glm::normalize(v);
    }
    template <class GenType>
    GenType normalize(GenType const &X)
    {
    return  glm::normalize(X);
    }

    template <class REAL>
    void normalizeVec3(Vector3<REAL>&V)
    {
    REAL len = V.length();
    V /= len;
    }

    template<class REAL>
    Matrix4<REAL> inverse(const Matrix4<REAL>&m)
    {
        return glm::inverse(m);
    }
    template <class REAL>
    void inverse(Matrix4<REAL>&m)
    {
        Matrix4<REAL> t;
        t = inverse(m);
        m = t;
    }

    template <class REAL>
    REAL dotVec3(const Vector3<REAL>&a,const Vector3<REAL>&b)
    {
    return glm::dot(a, b);
    }
    

    template <class REAL>
    REAL radinToDegree(const REAL&r)
    {
    REAL returnVal = (r * 180.0) / math::Const<REAL>::pi();
    return returnVal;
    }
    template <class REAL>
    REAL degreeToRadin(const REAL&d)
    {
    return (d * math::Const<REAL>::pi()) / 180.0;
    }
    
    inline bool closeEnough(float f1, float f2)
    {
    return fabsf((f1 - f2) / ((f2 == 0.0f) ? 1.0f : f2)) < 1e-6f;
    }
    
}
#endif /* Header_h */

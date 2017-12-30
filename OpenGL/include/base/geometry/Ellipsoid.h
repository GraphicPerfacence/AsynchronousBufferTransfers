//
//  Epllisoid.h
//  openGLTest
//
//  Created by xt on 17/12/10.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef Epllisoid_h
#define Epllisoid_h

#include "defType.hpp"
#include "math/HelpF.h"

    template<class REAL = float>
    class Ellipsoid
    {
    public:
        Ellipsoid (REAL a,REAL b,REAL c):
        _radii(a,b,c),
        _oneOverRadiiSquared(1.0 / (a * a),1.0 / (b * b),1.0 / (c * c))
        {

        }
        Vector3<REAL> radius()const {return _radii;}

        Vector3<REAL> geodeticSurfaceNormal(const Vector3<REAL>&v)
        {
            return math::normalize(v * _oneOverRadiiSquared);
        }
        
    private:
         Vector3<REAL> _radii;
         Vector3<REAL> _oneOverRadiiSquared;
    };



#endif /* Epllisoid_h */

//
//  Header.h
//  openGLTest
//
//  Created by xt on 17/8/28.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef OPENGL_M_HEAD_H
#define OPENGL_M_HEAD_H

    // Return value is 'true' if line segment intersects the current test
    // plane.  Otherwise 'false' is returned in which case the line segment
    // is entirely clipped.
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

#endif /* Header_h */

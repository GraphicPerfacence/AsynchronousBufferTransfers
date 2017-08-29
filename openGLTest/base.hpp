//
//  Base.hpp
//  openGLTest
//
//  Created by xt on 17/8/29.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef OPENGL_Base_hpp
#define OPENGL_Base_hpp

class Base
{
public:
    Base() : cRefs(0) { }
    virtual ~Base() { }

    void            NewRef() { ++cRefs; }

    void            DelRef()
    {
        if (--cRefs == 0)
        {
            delete this;
        } 
    }

    unsigned int getRefCount() const { return cRefs; }

private:
    unsigned int cRefs;
};

#include <stdio.h>

#endif /* Base_hpp */

//
//  Persisten.h
//  openGLTest
//
//  Created by xt on 17/8/30.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef OPENGL_PERSISTEM_H
#define OPENGL_PERSISTEM_H

#include "base.hpp"
#include <iostream>

class Persisten : public Base
{
public:
    virtual std::ostream&           Put(std::ostream&s)const {return s;}
    virtual std::iostream&          Get(std::iostream&i)const {return i;}
};

inline std::ostream& operator<<(std::ostream&s,const Persisten&p)
{
    return  p.Put(s);
}

inline std::iostream& operator>>(std::iostream&i,const Persisten&p)
{
    return p.Get(i);
}

#endif /* Persisten_h */

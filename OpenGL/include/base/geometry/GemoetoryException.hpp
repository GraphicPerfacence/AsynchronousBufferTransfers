//
//  GemoetoryException.hpp
//  openGLTest
//
//  Created by xt on 17/8/28.
//  Copyright © 2017年 xt. All rights reserved.
//

#ifndef _OPENGL_GemoetoryException_hpp
#define _OPENGL_GemoetoryException_hpp

#include <stdio.h>
#include "../Execption.hpp"

struct GeometryException : public BaseException
{
    GeometryException(const std::string& vMsg);
};

#endif /* GemoetoryException_hpp */

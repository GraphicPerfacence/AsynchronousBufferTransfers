//
//  BatchBase.h
//  OpenGL
//
//  Created by xt on 16/1/1.
//  Copyright (c) 2016年 xt. All rights reserved.
//
#ifndef __OpenGL_BATCH_BASE__
#define __OpenGL_BATCH_BASE__


#include <glm/glm.hpp>
#include "math3d.h"
////////////////////////////////////////////////////////////////////
// This base class is a pure virtual class with one single virtual 
// function, Draw(). The GLBegin class and GLTriangleBatch classes
// are derived from this. Having a virtual Draw() function allows
// these classes to be collected by container classes that can
// then iterate over them and call their draw methods. 

class BatchBase
{
public:
	virtual void Draw(void) = 0;
};


#endif
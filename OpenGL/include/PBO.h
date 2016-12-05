//
//  FBO.h
//  OpenGL
//
//  Created by xt on 16/1/1.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__PBO__
#define __OpenGL__PBO__

#include <cstddef>

class PBO
{
public:
	PBO();
	~PBO();
	void init(unsigned int num, ptrdiff_t size, const void* data, unsigned int  usage);
	unsigned int getObj(unsigned int i = 0) { return pixBuffer[i]; }
private:
	unsigned int  _num;
	unsigned int* pixBuffer;
};

#endif
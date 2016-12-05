#include "../include/PBO.h"
//
//  PBO.cpp
//  OpenGL
//
//  Created by xt on 16/1/1.
//  Copyright (c) 2016年 xt. All rights reserved.
//

#include <gl/glew.h>

PBO::PBO() :_num(1)
{

}
void PBO::init(unsigned int  num, ptrdiff_t size,
	const void * data,
	unsigned int  usage)
{
	_num = num;
	pixBuffer = new unsigned int[_num];

	glGenBuffers(num, pixBuffer);

	for (unsigned int  i = 0; i < _num; i++)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pixBuffer[i]);
		glBufferData(GL_PIXEL_PACK_BUFFER, size, data, usage);
		glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	}
}
PBO::~PBO()
{
	glDeleteTextures(_num, pixBuffer);
}
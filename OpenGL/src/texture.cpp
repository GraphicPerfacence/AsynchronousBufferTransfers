//
//  texture.cpp
//  OpenGL
//
//  Created by xt on 15/8/20.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/texture.h"
#include "../include/rgbTexture.h"
#include "../include/log.h"
#include "SOIL2/SOIL2.h"

#include <stdlib.h>
#include <stdio.h>

#include <GL/glew.h>

Texture::Texture() :_textureNum(1)
{
	texture = new unsigned int[1];
}

Texture::~Texture()
{
	for (unsigned int i = 0; i < _textureNum; i++)
		glDeleteTextures(1, &texture[i]);
}

Texture::Texture(int num)
{
	_textureNum = num;
	texture = new unsigned int[num];
}

unsigned int Texture::getTexture(unsigned int index)const
{
	return texture[index];
}

void Texture::init(unsigned int flag, unsigned int interalFormat, unsigned int format, 
	const char*imageFile)
{
	int width, height, channels;

	unsigned char* ht_map = SOIL_load_image(imageFile,&width, &height, &channels, flag);

	if (ht_map == 0)
	{
		printf("load texture %s fail...,and the error is %s", imageFile, SOIL_last_result());
		return;
	}

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, interalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, ht_map);
	//glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(ht_map);

}

void Texture::init(int n, unsigned int interalFormat, unsigned int format, unsigned int w, unsigned int h, 
	const void* data)
{
	glGenTextures(n, texture);

	for (unsigned int i = 0; i < n; i++)
	{
		glActiveTexture(GL_TEXTURE1 + i);
		glBindTexture(GL_TEXTURE_2D, texture[i]);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexImage2D(GL_TEXTURE_2D, 0, interalFormat, w, h, 0, format, GL_UNSIGNED_BYTE, data);
	}
}

void Texture::initRGBFile(const char* imgFile)
{
	static GLubyte *texData;
	GLfloat borderColor[4] = { 1.0, 1.0, 1.0, 1.0 };

	int width, height;
	int w, h;
	GLubyte *image, *img, *p;
	int i, j, components;

	image = (GLubyte *)read_rgb_texture(imgFile, &width, &height, &components);
	//w = width + 2 * 2;
	//h = height + 2 * 2;

	w = width;
	h = height;

	img = (GLubyte *)calloc(w * h, 4 * sizeof(unsigned char));

	p = img;
	//    for (j = -2; j < height + 2; ++j) {
	//        for (i = -2; i < width + 2; ++i) {

	for (j = 0; j < height; ++j) {
		for (i = 0; i < width; ++i) {
			if (0 <= j && j <= height - 1 && 0 <= i && i <= width - 1) {
				p[0] = image[4 * (j * width + i) + 0];
				p[1] = image[4 * (j * width + i) + 1];
				p[2] = image[4 * (j * width + i) + 2];
				p[3] = 0xff;
			}
			else {
				p[0] = borderColor[0] * 0xff;
				p[1] = borderColor[1] * 0xff;
				p[2] = borderColor[2] * 0xff;
				p[3] = borderColor[3] * 0xff;
			}
			p += 4;
		}
	}
	free(image);

	glGenTextures(1, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	//gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h,
	  //                GL_RGBA, GL_UNSIGNED_BYTE, img);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, img);
	glBindTexture(GL_TEXTURE_2D, 0);

}

void Texture::bind(void)
{
	if (texture[0])
	{
		glBindTexture(GL_TEXTURE_2D, texture[0]);
	}
}
void Texture::unBind(void)
{
	if (texture[0])
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
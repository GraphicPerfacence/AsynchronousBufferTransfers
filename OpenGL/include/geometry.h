//
//  geometry.h
//  OpenGL
//
//  Created by xt on 15/10/14.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__geometry__
#define __OpenGL__geometry__
#include <glm/glm.hpp>

void initPoints(unsigned int& pointVAO);
void drawPoints(const unsigned int& pointVAO);

void initQuad(unsigned int &QVAO);
void drawQuad(const unsigned int& QVAO);


void initScreenQuad(unsigned int&screenQuad);
void drawScreenQuad(const unsigned int&screenQuad);


void initCub(unsigned int&cubeVAO);
void drawCub(const unsigned int&cubeVAO, bool instance = false, unsigned int num = 0);

void initSkyBox(unsigned int &skyboxVAO);
void drawSkyBox(const unsigned int& skyboxVAO);

void initPlane(unsigned int& planeVAO);
void drawPlane(const unsigned int& planeVAO);


void generateOrtho2DMat(unsigned int screenWidth, unsigned int screenHeight,
	glm::mat4 &orthoMatrix);
    
void postAddInstanceModelMatrix(unsigned int index, unsigned int num, const glm::mat4* modes);
//for instance geomerty
glm::mat4 * instanceGeomModeMatrix(unsigned int amount);

#endif
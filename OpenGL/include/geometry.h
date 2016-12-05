//
//  geometry.h
//  OpenGL
//
//  Created by xt on 15/10/14.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__geometry__
#define __OpenGL__geometry__

#include "TriangleBatch.h"
#include "Batch.h"

void initPoints(unsigned int& pointVAO);
void drawPoints(unsigned int& pointVAO);

void initQuad(unsigned int &QVAO);
void drawQuad(unsigned int& QVAO);


void initScreenQuad(unsigned int&screenQuad);
void drawScreenQuad(unsigned int&screenQuad);


void initCub(unsigned int&cubeVAO);
void drawCub(unsigned int&cubeVAO, bool instance = false, unsigned int num = 0);

void initSkyBox(unsigned int &skyboxVAO);
void drawSkyBox(unsigned int& skyboxVAO);

void initTorus(TriangleBatch &, float majorRadius, float minorRadius, int numMajor, int numMinor);

void generateOrtho2DMat(unsigned int screenWidth, unsigned int screenHeight,
	Matrix &orthoMatrix, Batch &screenQuad);
void postAddInstanceModelMatrix(unsigned int index, unsigned int num, const glm::mat4* modes);
//for instance geomerty
Matrix * instanceGeomModeMatrix(unsigned int amount);

#endif
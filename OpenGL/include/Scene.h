//
//  Model.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__Model__
#define __OpenGL__Model__

#include "BaseRender.h"
#include "GLQuery.h"
#include "math3d.h"
#include <stdio.h>

class INode;

class Scene :public BaseRender
{
public:

	// Set the scale of our model to 100% by default
	Scene();
	~Scene() { Destroy(); }

	void Initialize();
	void initShader(void);
	void initSceneObjs(void);
	void initLight(void);
	void initFBO(void);
	void initBOs(unsigned int size);
	void initTexture(void);
	void initOpengl(void);
	void initThisDemo(void);
	// This draws the Model to the backbuffer
	void Render();

	// Create the getter and setters for the model's position
	Vec3f GetPosition() { return Position; }
	void SetPosition(Vec3f position) { Position = position; }

	// Create the getter and setters for the model's rotation
	Vec3f GetRotation() { return Rotation; }
	void SetRotation(Vec3f rotation) { Rotation = rotation; }

	// Create the getter and setters for the model's scale
	Vec3f GetScale() { return Scale; }
	void SetScale(Vec3f scale) { Scale = scale; }

	void setScreenWH(unsigned int w,unsigned int h);

	void Destroy();

protected:

	unsigned int bufferNum;

	unsigned int _screenWidth;
	unsigned int _screenHeight;

	Vec3f        Position;										// The model's position
	Vec3f        Rotation;										// The model's rotation
	Vec3f        Scale;											// The model's scale

	std::vector<INode*> _modes;
	std::vector<unsigned int> _fbos; // framebuffer object;
	std::vector<unsigned int> _textures; //texture objects

	GLQuery _query;
};


#endif /* defined(__OpenGL__Model__) */

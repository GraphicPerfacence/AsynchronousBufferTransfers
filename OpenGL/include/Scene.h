//
//  Model.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__Model__
#define __OpenGL__Model__
#include "Xtype.h"
#include "BaseRender.h"
#include "XGLQuery.h"
#include <stdio.h>

class Scene :public BaseRender
{
public:

	static const int BUILDING_SIDE_SIZE = 32;
	static const int MAX_BLOCK_COUNT = BUILDING_SIDE_SIZE *
            (BUILDING_SIDE_SIZE >> 1) * BUILDING_SIDE_SIZE * 2;

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

	
	//添加测试场景模型用来测试
	void createSceneData(void);


	// This draws the Model to the backbuffer
	void Render();

	Vec3f GetPosition() { return Position; }
	void SetPosition(Vec3f position) { Position = position; }

	Vec3f GetRotation() { return Rotation; }
	void SetRotation(Vec3f rotation) { Rotation = rotation; }

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

	std::vector<unsigned int> _fbos; // framebuffer object;
	std::vector<unsigned int> _textures; //texture objects

	XGLQuery _query;

};


#endif /* defined(__OpenGL__Model__) */

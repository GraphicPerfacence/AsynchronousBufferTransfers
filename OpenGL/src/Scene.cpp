//
//  Model.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/Scene.h"
#include "../include/GLFWManager.h"
#include "../include/shader.hpp"
#include "../include/TimerManager.h"
#include "../include/glfwSet.h"
#include "../include/mesh.h"
#include "../include/sys.h"
#include "../include/log.h"
#include "../include/camera.h"
#include "../include/geometry.h"
#include "../include/texture.h"
#include "SOIL2/SOIL2.h"

#include  <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <random>
#include <iostream>

const unsigned int NR_LIGHTS = 32;

///////////////////// Just For This Test//////////////////////////////

GLuint pixBufferIds[1];
GLuint textureId;

GLuint width = 1024;
GLuint height = 896;

GLuint objId;
GLuint textureID;
GLuint pboMode;

GLvoid*imageData;

const int DATA_SIZE = width * height * 4;
///////////////////////////////////////////////////////////////////


void updatePixels(GLubyte* dst, int size)
{
	static int color = 0;

	if(!dst)
		return;

	int* ptr = (int*)dst;

	// copy 4 bytes at once
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			*ptr = color;
			++ptr;
		}
		color += 257;   // add an arbitary number (no meaning)
	}
	++color;            // scroll down
}


Scene::Scene()
{
}

void Scene::Initialize()
{
	initOpengl();
	initLight();
	initSceneObjs();
	initShader();
	initTexture();
	initFBO();
	initThisDemo();
}

void Scene::initOpengl(void)
{
	//deafult the GL_CULL_FACE is disable
	//glEnable(GL_CULL_FACE); 
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

}

void Scene::initTexture(void)
{
	 
	//woodTexture.init(3,GL_RGB,GL_RGB,"D:/CODES/LearnOpenGL-master/resources/textures/wood.png");
	
	
	glGenTextures(1, &textureID);
	int width, height;
	unsigned char* image = SOIL_load_image("D:/CODES/LearnOpenGL-master/resources/textures/wood.png", 
		&width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	//woodTextureID =  textureID;

}

void Scene::initBOs(GLuint size)
{
	
}

void Scene::initFBO(void)
{
}

void Scene::initLight(void)
{
	 
}

void Scene::initShader(void)
{
	std::string  shaderBasePath;
#if defined X_OS_WIN32 || defined X_OS_WIN64
	shaderBasePath = "D:/projects/opengl/HDR/OpenGL/shader/";
#elif  __APPLE__
	shaderBasePath = "/Users/glp/Documents/projects/OpenGL/OpenGL/shader/";
#endif

	std::string vs = shaderBasePath + "hdr.vert";
	std::string fs = shaderBasePath + "hdr.frag";

	shaders.push_back(new Shader());
	shaders[0]->LoadShaders(vs.c_str(),fs.c_str());
	
	shaders[0]->TurnOn();
	GLint textureI = shaders[0]->GetVariable("hdrBuffer");
	shaders[0]->SetInt(textureI,0);
	shaders[0]->TurnOff();

}

void Scene::initSceneObjs(void)
{

#if defined X_OS_WIN32 || defined X_OS_WIN64
	
#elif defined __APPLE__

#endif
	
	initScreenQuad(objId);
}





void Scene::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader * currentShader = shaders[0];
	currentShader->TurnOn();


	
	_query.begin();
	glBindTexture(GL_TEXTURE_2D,textureID);
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_BGRA, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
	_query.end();
	GLuint64 timer = _query.time();
	//_query.swapQueryBuffers();

	std::cout << "GPU Milliseconds: " << timer << std::endl;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,textureID);
	drawScreenQuad(objId);
	glBindTexture(GL_TEXTURE_2D,0);
	currentShader->TurnOff();

	GLfloat timercpu = _query.getCurrentTime();

	updatePixels((GLubyte*)imageData, DATA_SIZE);

	GLfloat timercpu2 = _query.getCurrentTime();

	std::cout << "cpu: "  <<  timercpu2 - timercpu << std::endl;
}

// This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
void Scene::Destroy()
{
	for (int i = shaders.size() - 1; i >= 0; i--)
	{
		Shader * s = shaders[i];
		s->Destroy();
		s = NULL;
	}

	for(unsigned int i = 0;i < _modes.size();i++)
	{
		delete _modes[i];
		_modes[i] = NULL;
	}

	for(unsigned int i = 0;i < _textures.size();i++)
	{
		glDeleteBuffers(1,&_textures[i]);
	}

	for(unsigned int i = 0;i < _fbos.size();i++)
	{
		glDeleteFramebuffers(1,&_fbos[i]);
	}
}

void Scene::initThisDemo(void)
{
	//texture for update
	glGenTextures(1,&textureId);
	glBindTexture(GL_TEXTURE_2D,textureId);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 1.0f);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE ,NULL);

	//PBO
	glGenBuffers(1,&pixBufferIds[0]);
	//GL_STREAM_DRAW  for texture upload
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[0]);
 	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4,NULL,GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

	//imageData
	imageData = new GLubyte[DATA_SIZE];
	memset(imageData, 0, DATA_SIZE);

	//generate Query
	
	_query.genQueries();

}

void Scene::setScreenWH(unsigned int w,unsigned int h)
{
	_screenWidth = w;
	_screenHeight = h;
}

void modelInput(InputCodes code)
{
	switch (code)
	{
	case  InputCodes::b:
		 
		break;
	case  InputCodes::c:
		 
		break;
	case InputCodes::u:
		break;
	case InputCodes::y:
		break;
	default:
		break;
	}
}

void windowSize(GLFWwindow*window, int width, int height)  
{
	glViewport(0, 0, width, height);
}

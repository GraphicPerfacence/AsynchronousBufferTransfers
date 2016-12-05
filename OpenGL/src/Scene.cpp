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
#include "../include/Timer.h"

#include  <glm/gtc/type_ptr.hpp>

#include <string>
#include <vector>
#include <random>
#include <iostream>

const unsigned int NR_LIGHTS = 32;

///////////////////// Just For This Test//////////////////////////////

GLuint pixBufferIds[2];
GLuint textureId;

GLuint width = 1024;
GLuint height = 896;

GLuint objId;
GLuint pboMode;

GLvoid*imageData;

const int DATA_SIZE = width * height * 4;
const GLenum PIXEL_FORMAT    = GL_BGRA;

float copyTime, updateTime;
Timer timer, t1, t2;
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

	static int index = 0;
	int nextIndex = 0;   

	if(pboMode == 0)
	{
		// cpu -> gpu noraml
		
		t1.start();
		glBindTexture(GL_TEXTURE_2D,textureId);
		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, PIXEL_FORMAT, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
		t1.stop();
		copyTime = t1.getElapsedTimeInMilliSec();

		std::cout << "GPU Milliseconds: " << copyTime << std::endl;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,textureId);
		drawScreenQuad(objId);
		glBindTexture(GL_TEXTURE_2D,0);
		currentShader->TurnOff();

		//update image Data
		GLfloat timercpu = _query.getCurrentTime();
		updatePixels((GLubyte*)imageData, DATA_SIZE);
		GLfloat timercpu2 = _query.getCurrentTime();

		std::cout << "cpu Milliseconds : "  <<  timercpu2 - timercpu << std::endl;
	}

	//one pbo
	else if(pboMode == 1 ||  pboMode == 2)
	{
		if(pboMode == 1)
			index = nextIndex = 0; //single PBO
		else 
		{
			index = (index + 1) % 2; //double PBO
			nextIndex = (index + 1) % 2;
		}

		//update texture 
		t1.start();
		glBindTexture(GL_TEXTURE_2D,textureId);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[index]);
		glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,PIXEL_FORMAT,GL_UNSIGNED_BYTE,NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
		t1.stop();
		copyTime = t1.getElapsedTimeInMilliSec();
		std::cout << "GPU Milliseconds: " << copyTime << std::endl;

		GLuint64 cpuTimer = _query.getCurrentTime();
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[nextIndex]);
		// map the buffer object into client's memory
		// Note that glMapBufferARB() causes sync issue.
		// If GPU is working with this buffer, glMapBufferARB() will wait(stall)
		// for GPU to finish its job. To avoid waiting (stall), you can call
		// first glBufferDataARB() with NULL pointer before glMapBufferARB().
		// If you do that, the previous data in PBO will be discarded and
		// glMapBufferARB() returns a new allocated pointer immediately
		// even if GPU is still working with the previous data.
		glBufferData(GL_PIXEL_UNPACK_BUFFER,DATA_SIZE,NULL,GL_STREAM_DRAW);
		GLubyte * prt =  (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER,GL_WRITE_ONLY);

		if(prt)
		{
			updatePixels(prt,DATA_SIZE);
			glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
		}
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
		GLuint64 cpuTimer2 = _query.getCurrentTime();

		std::cout << "update imageData: "  << cpuTimer2 - cpuTimer << std::endl;

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,textureId);
		drawScreenQuad(objId);
		glBindTexture(GL_TEXTURE_2D,0);
		currentShader->TurnOff();
	}
	 
	
	
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

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,PIXEL_FORMAT,GL_UNSIGNED_BYTE ,NULL);
	glBindTexture(GL_TEXTURE_2D,0);

	//PBO
	glGenBuffers(2,&pixBufferIds[0]);
	//GL_STREAM_DRAW  for texture upload
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[0]);
 	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4,NULL,GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[1]);
	glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4,NULL,GL_STREAM_DRAW);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

	//imageData for texture
	imageData = new GLubyte[DATA_SIZE];
	memset(imageData, 0, DATA_SIZE);

	//generate Query
	
	_query.genQueries();

	pboMode= 2;
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

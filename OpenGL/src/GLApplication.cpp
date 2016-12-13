//
//  GLApplication.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/GLApplication.h"
#include "../include/TimerManager.h"
#include "../include/camera.h"
#include "../include/Scene.h"
#include "../include/log.h"
										// Our class to handle initializing and drawing our triangle

// This is our own main() function which abstracts the required main() function to run this application.
int GLApplication::GLMain()
{
	Initialize();
	GameLoop();
	return 0;
}

void GLApplication::openglInit(void)
{

}
// This function initializes the window, the shaders and the triangle vertex data.
void GLApplication::Initialize()
{
	// Make sure the window manager is initialized prior to calling this and creates the OpenGL context
	if (!WindowManager || WindowManager->Initialize(&_width, &_hight, "GameTutorials - Camera", _isFullScreen) != 0)
	{
		exit(-1);
	}

	glViewport(0, 0, _width, _hight);
	
	glClearColor(0.3f, 0.2f, 0.4f, 1.0f);

	openglInit();
	// Initialize the triangle with the vertex array and give the length of 3.  This will create our
	// Vertex Buffer Object and Vertex Array Object.
	Camera->SetPerspective(45.0f, _width / (float)_hight, 0.1f, 100.f);

	// Below we call our init function for our camera to give it a position, a yaw and a pitch rotation.
	// 0 for a yaw and pitch will put the camera looking directly down the negative z-axis.  We don't
	// do any rotations yet so a different pitch or yaw won't do anything until our next tutorial.

	//					  Position	  
	Camera->PositionCamera(0, 0, 5, 0, 0, 0, 0, 1, 0);
	Camera->SetSpeed(0.06);

	_scene = new Scene();
	_scene->setScreenWH(_width,_hight);
	_scene->SetCamera(Camera);

	if (!rOGLText::initTextLib())
	{
		return;
	}

	_scene->Initialize();


}


// This is our game loop where all the magic happens every frame
void GLApplication::GameLoop()
{
	// Loop until the user hits the Escape key or closes the window
	while (WindowManager->ProcessInput(true))
	{
		// Use our Singleton to calculate our framerate every frame, passing true to set FPS in titlebar
		TimeManager::Instance().CalculateFrameRate(false);

		// This clears the screen every frame to black (color can be changed with glClearColor)
		Camera->updateData();

		_scene->SetPosition(vec3(0, 0, 0));
		_scene->Render();

		WindowManager->SwapTheBuffers();
	}
}

void GLApplication::initScene()
{
	glShadeModel(GL_SMOOTH);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glReadBuffer(GL_BACK);
	glDrawBuffer(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glDepthMask(GL_TRUE);
	glDisable(GL_STENCIL_TEST);
	glStencilMask(0xFFFFFFFF);
	glStencilFunc(GL_EQUAL, 0x00000000, 0x00000001);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
	glClearDepth(1.0);
	glClearStencil(0);
	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_DITHER);
	//glActiveTexture(GL_TEXTURE0);

}

// This can be used to free all of our resources in the application.
void GLApplication::Destroy()
{
	// If we have a window manager still allocated then destroy and delete it
	if (WindowManager)
	{
		WindowManager->Destroy();

		delete WindowManager;
		WindowManager = nullptr;
	}


	// If we have the camera still, delete it
	if (Camera)
	{
		delete Camera;
		Camera = nullptr;
	}

	delete _scene;
	Log::Instance()->Destroy();
}

GLApplication::GLApplication(bool isFullScreen)
{
	 _isFullScreen = isFullScreen;
	 _width = 1200;
	 _hight = 900;
}

void GLApplication::setApplication(unsigned int w,unsigned int h)
{
	_width = w;
	_hight = h;
}

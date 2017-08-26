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
#include "../include/XText.h"
										

int GLApplication::GLMain()
{
	Initialize();
	GameLoop();
	return 0;
}

void GLApplication::OpenglInit(void)
{

}

GLFWManager *  GLApplication::GetWindowManager()const
{
    return  _windowManager;
}
void  GLApplication::SetWindowManager(GLFWManager *pWindowManager)
{
    _windowManager = pWindowManager;
}

void GLApplication::Initialize()
{
	// Make sure the window manager is initialized prior to calling this and creates the OpenGL context
	if (!_windowManager || _windowManager->Initialize(&_width, &_hight, "GameTutorials - Camera", _isFullScreen) != 0)
	{
		exit(-1);
	}

	glViewport(0, 0, _width, _hight);
	
	glClearColor(0.3f, 0.2f, 0.4f, 1.0f);

	OpenglInit();
    GetCamera()->SetPerspective(45.0f, _width / (float)_hight, 0.1f, 100.f);

	_scene = new Scene();
	_scene->setScreenWH(_width,_hight);
	_scene->SetCamera(GetCamera());

    //XText::initTextLib();
	_scene->Initialize();

}


// This is our game loop where all the magic happens every frame
void GLApplication::GameLoop()
{
	// Loop until the user hits the Escape key or closes the window
	while (_windowManager->ProcessInput(true))
	{
		// Use our Singleton to calculate our framerate every frame, passing true to set FPS in titlebar
		TimeManager::Instance().CalculateFrameRate(false);

		// This clears the screen every frame to black (color can be changed with glClearColor)
		//Camera->updateData();

		_scene->SetPosition(vec3(0, 0, 0));
		_scene->Render();

		_windowManager->SwapTheBuffers();
	}
}

void GLApplication::InitScene()
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
	if (_windowManager)
	{
		_windowManager->Destroy();

		delete _windowManager;
		_windowManager = nullptr;
	}

	delete _scene;
	Log::Instance()->Destroy();
}

Camera *  GLApplication::GetCamera()const
{
    if(_windowManager != NULL)
    {
        return _windowManager->GetCamera();
    }

    return  NULL;
}

GLApplication::GLApplication(bool isFullScreen):
    _windowManager(NULL)
{
	 _isFullScreen = isFullScreen;
	 _width = 1200;
	 _hight = 900;
}

void GLApplication::SetApplication(unsigned int w,unsigned int h)
{
	_width = w;
	_hight = h;
}

//
//  GLFWManager.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//
#include <iostream>

#include "GLFWManager.h"
#include "glfwSet.h"
#include "comm.h"
#include "sys.h"
#include "log.h"


GLFWManager::GLFWManager(CameraEx<float>* c)
{
    _camera = c;
}

GLFWManager::~GLFWManager()
{
    Destroy();
}

int GLFWManager::Initialize(unsigned int* width, unsigned int* height, std::string strTitle, bool bFullScreen,
	bool core)
{
	if (!glfwInit())
	{
		printf( "Failed to initialize GLFW\n");
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	#if defined __APPLE__
	if (core)
	{
        // Set our OpenGL version to 4 using the core profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
#endif
	glfwSetErrorCallback(Log::GLFWError);


	if (bFullScreen)
	{
		GLFWmonitor * wMonitor =  glfwGetPrimaryMonitor();
		
		const GLFWvidmode*  vidmode = glfwGetVideoMode(wMonitor);

		_window = glfwCreateWindow(*width, *height, strTitle.c_str(), wMonitor, nullptr);

		*width = vidmode->width;
		*height = vidmode->height;
	}
	else
		_window = glfwCreateWindow(*width, *height, strTitle.c_str(), nullptr, nullptr);

	if (_window == nullptr)
	{
		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		Destroy();
		return -1;
	}

	
	glfwMakeContextCurrent(_window);

	// This turns on STICKY_KEYS for keyboard input
	glfwSetInputMode(_window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	glfwSetMouseButtonCallback(_window, InputManager::Instance().mouse_button_callback);
	glfwSetCursorPosCallback(_window, InputManager::Instance().mouse_curse_pos_callback);
    glfwSetScrollCallback(_window,InputManager::Instance().mouse_scroll_callback);


	glfwSetCursorPos(_window, 0, 0);

	// This turns off the vertical sync to your monitor so it renders as fast as possible
   // glfwSwapInterval(0);

	// Tell GLEW to grab all the OpenGL functions and extensions even if "experimental"
	glewExperimental = GL_TRUE;

	glfwSetWindowSizeCallback(_window, windowSize);

	GLenum err = glewInit();

	if (GLEW_OK != err)
	{
		fprintf(stderr, "Failed to initialize glew\n");
		return -1;
	}

	//testOpenGl();

    return 0;
}
void GLFWManager::SwapTheBuffers()
{
	glfwSwapBuffers(_window);
}

void GLFWManager::Destroy()
{
    glfwTerminate();
}

const GLFWwindow* GLFWManager::GetWindow()
{
	return _window;
}

CameraEx<float>* GLFWManager::GetCamera(void)const
{
    return  _camera;
}

bool GLFWManager::ProcessInput(bool continueGame = true)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(_window) != 0)
		return false;

    InputManager::Instance().ClearMoveVec();
    
	if (glfwGetKey(_window, GLFW_KEY_LEFT) )
		InputManager::Instance().KeyPressed(Left);
	else if (glfwGetKey(_window, GLFW_KEY_RIGHT))
		InputManager::Instance().KeyPressed(Right);
	else if (glfwGetKey(_window, GLFW_KEY_UP))
		InputManager::Instance().KeyPressed(Up);
	else if (glfwGetKey(_window, GLFW_KEY_DOWN))
		InputManager::Instance().KeyPressed(Down);
	// down key for shader uniform test
	else if (glfwGetKey(_window, GLFW_KEY_A))
		InputManager::Instance().KeyPressed(InputCodes::a);
	else if (glfwGetKey(_window, GLFW_KEY_B))
		InputManager::Instance().KeyPressed(InputCodes::b);
	else if (glfwGetKey(_window, GLFW_KEY_C))
		InputManager::Instance().KeyPressed(InputCodes::c);
	else if (glfwGetKey(_window, GLFW_KEY_D))
		InputManager::Instance().KeyPressed(InputCodes::d);
	else if (glfwGetKey(_window, GLFW_KEY_E))
		InputManager::Instance().KeyPressed(InputCodes::e);
	else if (glfwGetKey(_window, GLFW_KEY_F))
		InputManager::Instance().KeyPressed(InputCodes::f);
	else if (glfwGetKey(_window, GLFW_KEY_G))
		InputManager::Instance().KeyPressed(InputCodes::g);
	else if (glfwGetKey(_window, GLFW_KEY_H))
		InputManager::Instance().KeyPressed(InputCodes::h);
	else if (glfwGetKey(_window, GLFW_KEY_I))
		InputManager::Instance().KeyPressed(InputCodes::i);
	else if (glfwGetKey(_window, GLFW_KEY_J))
		InputManager::Instance().KeyPressed(InputCodes::j);
	else if (glfwGetKey(_window, GLFW_KEY_K))
		InputManager::Instance().KeyPressed(InputCodes::k);
	else if (glfwGetKey(_window, GLFW_KEY_L))
		InputManager::Instance().KeyPressed(InputCodes::l);
	else if (glfwGetKey(_window, GLFW_KEY_M))
		InputManager::Instance().KeyPressed(InputCodes::m);
	else if (glfwGetKey(_window, GLFW_KEY_N))
		InputManager::Instance().KeyPressed(InputCodes::n);
	else if (glfwGetKey(_window, GLFW_KEY_O))
		InputManager::Instance().KeyPressed(InputCodes::o);
	else if (glfwGetKey(_window, GLFW_KEY_P))
		InputManager::Instance().KeyPressed(InputCodes::p);
	else if (glfwGetKey(_window, GLFW_KEY_Q))
		InputManager::Instance().KeyPressed(InputCodes::q);
	else if (glfwGetKey(_window, GLFW_KEY_R))
		InputManager::Instance().KeyPressed(InputCodes::R);
	else if (glfwGetKey(_window, GLFW_KEY_S))
		InputManager::Instance().KeyPressed(InputCodes::s);
	else if (glfwGetKey(_window, GLFW_KEY_T))
		InputManager::Instance().KeyPressed(InputCodes::t);
	else if (glfwGetKey(_window, GLFW_KEY_U))
		InputManager::Instance().KeyPressed(InputCodes::u);
	else if (glfwGetKey(_window, GLFW_KEY_V))
		InputManager::Instance().KeyPressed(InputCodes::v);
	else if (glfwGetKey(_window, GLFW_KEY_W))
		InputManager::Instance().KeyPressed(InputCodes::w);
	else if (glfwGetKey(_window, GLFW_KEY_X))
		InputManager::Instance().KeyPressed(InputCodes::x);
	else if (glfwGetKey(_window, GLFW_KEY_Y))
		InputManager::Instance().KeyPressed(InputCodes::y);
	else if (glfwGetKey(_window, GLFW_KEY_Z))
		InputManager::Instance().KeyPressed(InputCodes::z);

   
	glfwPollEvents();

	return continueGame;
}
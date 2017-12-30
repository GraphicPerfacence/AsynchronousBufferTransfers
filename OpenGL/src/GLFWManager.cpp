//
//  GLFWManager.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//
#include <iostream>

#include "GLFWManager.h"
#include "comm.h"
#include "sys.h"
#include "log.h"

extern void  mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
extern void  mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse);
extern void  mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos);
extern void  windowSize(GLFWwindow*window, int width, int height);
extern void  key_callback(GLFWwindow*window,int,int,int,int);

GLFWManager::GLFWManager(Camera* c)
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
	glfwSetMouseButtonCallback(_window, mouse_button_callback);
	glfwSetCursorPosCallback(_window, mouse_curse_pos_callback);
    glfwSetScrollCallback(_window,mouse_scroll_callback);
    glfwSetKeyCallback(_window, key_callback);

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

    _inputManager = InputManager::Instance();
    _inputManager->SetCamera(_camera);
    return 0;
}
void GLFWManager::SwapTheBuffers()
{
	glfwSwapBuffers(_window);
}

void GLFWManager::Destroy()
{

    glfwTerminate();

    if(_inputManager != NULL)
    {
        delete _inputManager;
        _inputManager = NULL;
    }
}

const GLFWwindow* GLFWManager::GetWindow()
{
	return _window;
}

Camera* GLFWManager::GetCamera(void)const
{
    return  _camera;
}

bool GLFWManager::ShouldeClose()const
{
    return  glfwWindowShouldClose(_window);
}

void GLFWManager::CloseWindow()
{
    glfwDestroyWindow(_window);
}

bool GLFWManager::ProcessInput(bool continueGame = true)
{
	   
	glfwPollEvents();

	return continueGame;
}

InputManager*   GLFWManager::GetInputManager()
{
    return _inputManager;
}
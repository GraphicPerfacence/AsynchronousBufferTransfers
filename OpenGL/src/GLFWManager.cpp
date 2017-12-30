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
extern void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos);
extern void windowSize(GLFWwindow*window, int width, int height);


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

    _inputManager = new InputManager(_window);
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

bool GLFWManager::ProcessInput(bool continueGame = true)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS ||
        glfwWindowShouldClose(_window) != 0)
		return false;

    _inputManager->MouseProcess();
    
	if (glfwGetKey(_window, GLFW_KEY_LEFT) )
		_inputManager->KeyPressed(Left);
	else if (glfwGetKey(_window, GLFW_KEY_RIGHT))
		_inputManager->KeyPressed(Right);
	else if (glfwGetKey(_window, GLFW_KEY_UP))
		_inputManager->KeyPressed(Up);
	else if (glfwGetKey(_window, GLFW_KEY_DOWN))
		_inputManager->KeyPressed(Down);
	// down key for shader uniform test
	else if (glfwGetKey(_window, GLFW_KEY_A))
		_inputManager->KeyPressed(InputCodes::a);
	else if (glfwGetKey(_window, GLFW_KEY_B))
		_inputManager->KeyPressed(InputCodes::b);
	else if (glfwGetKey(_window, GLFW_KEY_C))
		_inputManager->KeyPressed(InputCodes::c);
	else if (glfwGetKey(_window, GLFW_KEY_D))
		_inputManager->KeyPressed(InputCodes::d);
	else if (glfwGetKey(_window, GLFW_KEY_E))
		_inputManager->KeyPressed(InputCodes::e);
	else if (glfwGetKey(_window, GLFW_KEY_F))
		_inputManager->KeyPressed(InputCodes::f);
	else if (glfwGetKey(_window, GLFW_KEY_G))
		_inputManager->KeyPressed(InputCodes::g);
	else if (glfwGetKey(_window, GLFW_KEY_H))
		_inputManager->KeyPressed(InputCodes::h);
	else if (glfwGetKey(_window, GLFW_KEY_I))
		_inputManager->KeyPressed(InputCodes::i);
	else if (glfwGetKey(_window, GLFW_KEY_J))
		_inputManager->KeyPressed(InputCodes::j);
	else if (glfwGetKey(_window, GLFW_KEY_K))
		_inputManager->KeyPressed(InputCodes::k);
	else if (glfwGetKey(_window, GLFW_KEY_L))
		_inputManager->KeyPressed(InputCodes::l);
	else if (glfwGetKey(_window, GLFW_KEY_M))
		_inputManager->KeyPressed(InputCodes::m);
	else if (glfwGetKey(_window, GLFW_KEY_N))
		_inputManager->KeyPressed(InputCodes::n);
	else if (glfwGetKey(_window, GLFW_KEY_O))
		_inputManager->KeyPressed(InputCodes::o);
	else if (glfwGetKey(_window, GLFW_KEY_P))
		_inputManager->KeyPressed(InputCodes::p);
	else if (glfwGetKey(_window, GLFW_KEY_Q))
		_inputManager->KeyPressed(InputCodes::q);
	else if (glfwGetKey(_window, GLFW_KEY_R))
		_inputManager->KeyPressed(InputCodes::R);
	else if (glfwGetKey(_window, GLFW_KEY_S))
		_inputManager->KeyPressed(InputCodes::s);
	else if (glfwGetKey(_window, GLFW_KEY_T))
		_inputManager->KeyPressed(InputCodes::t);
	else if (glfwGetKey(_window, GLFW_KEY_U))
		_inputManager->KeyPressed(InputCodes::u);
	else if (glfwGetKey(_window, GLFW_KEY_V))
		_inputManager->KeyPressed(InputCodes::v);
	else if (glfwGetKey(_window, GLFW_KEY_W))
		_inputManager->KeyPressed(InputCodes::w);
	else if (glfwGetKey(_window, GLFW_KEY_X))
		_inputManager->KeyPressed(InputCodes::x);
	else if (glfwGetKey(_window, GLFW_KEY_Y))
		_inputManager->KeyPressed(InputCodes::y);
	else if (glfwGetKey(_window, GLFW_KEY_Z))
		_inputManager->KeyPressed(InputCodes::z);

   
	glfwPollEvents();

	return continueGame;
}

InputManager*   GLFWManager::GetInputManager()
{
    return _inputManager;
}
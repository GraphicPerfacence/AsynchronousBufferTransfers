//
//  GLFWManager.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//
#include <iostream>

#include "../include/GLFWManager.h"
#include "../include/glfwSet.h"
#include "../include/comm.h"
#include "../include/sys.h"

GLFWwindow* g_Window;





static Camera * _localCamera;
static bool btnPress = false;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if(action == GLFW_PRESS)
    {
        btnPress = true;
    }
    else if(action == GLFW_RELEASE)
    {
        btnPress = false;
    }
    else if(action == GLFW_REPEAT)
    {

    }
}
void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(btnPress)
    {
        static bool firstMouse = true;
        static float lastX;
        static float lastY;

        if(firstMouse)
        {
            lastX = xpos;
            lastY = ypos;

            firstMouse = false;
        }

        GLfloat xoffset = xpos - lastX;
        GLfloat yoffset = ypos - lastY;

        lastX = xpos;
        lastY = ypos;

        _localCamera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void mouse_scroll_callback (GLFWwindow *, double xoffse, double yoffse)
{
    _localCamera->ProcessMouseScroll(yoffse * 0.1);
}

void error_callback(int error, const char* description)
{
	std::cout << "glfw error: " << description << std::endl;
}

GLFWManager::GLFWManager(Camera* c)
{
    _camera = c;
    _localCamera = _camera;
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
	glfwSetErrorCallback(error_callback);

	// Create a window either in full screen or not
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

	g_Window = _window;
	// Make sure the window is valid, if not, throw an error.
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

	// Set the cursor position of the hidden mouse to be in the top left of the window.
	// This way we can get a delta of the mouse position from (0, 0) and reset it again.
	glfwSetCursorPos(_window, 0, 0);

	// This turns off the vertical sync to your monitor so it renders as fast as possible
   // glfwSwapInterval(0);

	// Tell GLEW to grab all the OpenGL functions and extensions even if "experimental"
	glewExperimental = GL_TRUE;

	glfwSetWindowSizeCallback(_window, windowSize);

	// Initialize the GLEW library and attach all the OpenGL functions and extensions
	GLenum err = glewInit();

	// If we had an error, return -1.  Be sure to see if glewExperimental isn't true, this worked for me.
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
	// This closes the OpenGL window and terminates the application
	glfwTerminate();
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
	// Use the GLFW function to check for the user pressing the Escape button, as well as a window close event.
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(_window) != 0)
		return false;

	if (glfwGetKey(_window, GLFW_KEY_LEFT) )
		_inputManager.KeyPressed(Left);
	if (glfwGetKey(_window, GLFW_KEY_RIGHT))
		_inputManager.KeyPressed(Right);
	if (glfwGetKey(_window, GLFW_KEY_UP))
		_inputManager.KeyPressed(Up);
	if (glfwGetKey(_window, GLFW_KEY_DOWN))
		_inputManager.KeyPressed(Down);
	// down key for shader uniform test
	if (glfwGetKey(_window, GLFW_KEY_A))
		_inputManager.KeyPressed(InputCodes::a);
	if (glfwGetKey(_window, GLFW_KEY_B))
		_inputManager.KeyPressed(InputCodes::b);
	if (glfwGetKey(_window, GLFW_KEY_C))
		_inputManager.KeyPressed(InputCodes::c);
	if (glfwGetKey(_window, GLFW_KEY_D))
		_inputManager.KeyPressed(InputCodes::d);
	if (glfwGetKey(_window, GLFW_KEY_E))
		_inputManager.KeyPressed(InputCodes::e);
	if (glfwGetKey(_window, GLFW_KEY_F))
		_inputManager.KeyPressed(InputCodes::f);
	if (glfwGetKey(_window, GLFW_KEY_G))
		_inputManager.KeyPressed(InputCodes::g);
	if (glfwGetKey(_window, GLFW_KEY_H))
		_inputManager.KeyPressed(InputCodes::h);
	if (glfwGetKey(_window, GLFW_KEY_I))
		_inputManager.KeyPressed(InputCodes::i);
	if (glfwGetKey(_window, GLFW_KEY_J))
		_inputManager.KeyPressed(InputCodes::j);
	if (glfwGetKey(_window, GLFW_KEY_K))
		_inputManager.KeyPressed(InputCodes::k);
	if (glfwGetKey(_window, GLFW_KEY_L))
		_inputManager.KeyPressed(InputCodes::l);
	if (glfwGetKey(_window, GLFW_KEY_M))
		_inputManager.KeyPressed(InputCodes::m);
	if (glfwGetKey(_window, GLFW_KEY_N))
		_inputManager.KeyPressed(InputCodes::n);
	if (glfwGetKey(_window, GLFW_KEY_O))
		_inputManager.KeyPressed(InputCodes::o);
	if (glfwGetKey(_window, GLFW_KEY_P))
		_inputManager.KeyPressed(InputCodes::p);
	if (glfwGetKey(_window, GLFW_KEY_Q))
		_inputManager.KeyPressed(InputCodes::q);
	if (glfwGetKey(_window, GLFW_KEY_R))
		_inputManager.KeyPressed(InputCodes::R);
	if (glfwGetKey(_window, GLFW_KEY_S))
		_inputManager.KeyPressed(InputCodes::s);
	if (glfwGetKey(_window, GLFW_KEY_T))
		_inputManager.KeyPressed(InputCodes::t);
	if (glfwGetKey(_window, GLFW_KEY_U))
		_inputManager.KeyPressed(InputCodes::u);
	if (glfwGetKey(_window, GLFW_KEY_V))
		_inputManager.KeyPressed(InputCodes::v);
	if (glfwGetKey(_window, GLFW_KEY_W))
		_inputManager.KeyPressed(InputCodes::w);
	if (glfwGetKey(_window, GLFW_KEY_X))
		_inputManager.KeyPressed(InputCodes::x);
	if (glfwGetKey(_window, GLFW_KEY_Y))
		_inputManager.KeyPressed(InputCodes::y);
	if (glfwGetKey(_window, GLFW_KEY_Z))
		_inputManager.KeyPressed(InputCodes::z);

   // glfwSetCursorPos(Window, 0, 0);


	glfwPollEvents();

	return continueGame;
}
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

extern void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
extern void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos);
extern void mouse_scroll_callback (GLFWwindow *, double xoffse, double yoffse);

void error_callback(int error, const char* description)
{
	std::cout << "glfw error: " << description << std::endl;
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

	// Set our OpenGL version to 4 using the core profile
#if defined X_OS_MACX || defined X_OS_MACX
	if (core)
	{
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

		Window = glfwCreateWindow(*width, *height, strTitle.c_str(), wMonitor, nullptr);

		*width = vidmode->width;
		*height = vidmode->height;
	}
	else
		Window = glfwCreateWindow(*width, *height, strTitle.c_str(), nullptr, nullptr);

	g_Window = Window;
	// Make sure the window is valid, if not, throw an error.
	if (Window == nullptr)
	{
		fprintf(stderr, "Failed to create a GLFW window, you might need to download the latest drivers or change the OpenGL version to 3\n");
		Destroy();
		return -1;
	}

	// Create the OpenGL context from the window and settings specified
	glfwMakeContextCurrent(Window);

	// This turns on STICKY_KEYS for keyboard input
	glfwSetInputMode(Window, GLFW_STICKY_KEYS, GL_TRUE);
	// We want to hide the mouse since it will be used to move the camera's view around
	// and don't want to see it being pushed up into the top left corner.
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	glfwSetMouseButtonCallback(Window, mouse_button_callback);

	glfwSetCursorPosCallback(Window, mouse_curse_pos_callback);

	glfwSetScrollCallback(Window,mouse_scroll_callback);

	// Set the cursor position of the hidden mouse to be in the top left of the window.
	// This way we can get a delta of the mouse position from (0, 0) and reset it again.
	glfwSetCursorPos(Window, 0, 0);

	// This turns off the vertical sync to your monitor so it renders as fast as possible
   // glfwSwapInterval(0);

	// Tell GLEW to grab all the OpenGL functions and extensions even if "experimental"
	glewExperimental = GL_TRUE;

	glfwSetWindowSizeCallback(Window, windowSize);

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
	glfwSwapBuffers(Window);
}

void GLFWManager::Destroy()
{
	// This closes the OpenGL window and terminates the application
	glfwTerminate();
}

const GLFWwindow* GLFWManager::getWindow()
{
	return Window;
}
bool GLFWManager::ProcessInput(bool continueGame = true)
{
	// Use the GLFW function to check for the user pressing the Escape button, as well as a window close event.
	if (glfwGetKey(Window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwWindowShouldClose(Window) != 0)
		return false;

	if (glfwGetKey(Window, GLFW_KEY_LEFT) )
		InputManager.KeyPressed(Left);
	if (glfwGetKey(Window, GLFW_KEY_RIGHT))
		InputManager.KeyPressed(Right);
	if (glfwGetKey(Window, GLFW_KEY_UP))
		InputManager.KeyPressed(Up);
	if (glfwGetKey(Window, GLFW_KEY_DOWN))
		InputManager.KeyPressed(Down);
	// down key for shader uniform test
	if (glfwGetKey(Window, GLFW_KEY_A))
		InputManager.KeyPressed(InputCodes::a);
	if (glfwGetKey(Window, GLFW_KEY_B))
		InputManager.KeyPressed(InputCodes::b);
	if (glfwGetKey(Window, GLFW_KEY_C))
		InputManager.KeyPressed(InputCodes::c);
	if (glfwGetKey(Window, GLFW_KEY_D))
		InputManager.KeyPressed(InputCodes::d);
	if (glfwGetKey(Window, GLFW_KEY_E))
		InputManager.KeyPressed(InputCodes::e);
	if (glfwGetKey(Window, GLFW_KEY_F))
		InputManager.KeyPressed(InputCodes::f);
	if (glfwGetKey(Window, GLFW_KEY_G))
		InputManager.KeyPressed(InputCodes::g);
	if (glfwGetKey(Window, GLFW_KEY_H))
		InputManager.KeyPressed(InputCodes::h);
	if (glfwGetKey(Window, GLFW_KEY_I))
		InputManager.KeyPressed(InputCodes::i);
	if (glfwGetKey(Window, GLFW_KEY_J))
		InputManager.KeyPressed(InputCodes::j);
	if (glfwGetKey(Window, GLFW_KEY_K))
		InputManager.KeyPressed(InputCodes::k);
	if (glfwGetKey(Window, GLFW_KEY_L))
		InputManager.KeyPressed(InputCodes::l);
	if (glfwGetKey(Window, GLFW_KEY_M))
		InputManager.KeyPressed(InputCodes::m);
	if (glfwGetKey(Window, GLFW_KEY_N))
		InputManager.KeyPressed(InputCodes::n);
	if (glfwGetKey(Window, GLFW_KEY_O))
		InputManager.KeyPressed(InputCodes::o);
	if (glfwGetKey(Window, GLFW_KEY_P))
		InputManager.KeyPressed(InputCodes::p);
	if (glfwGetKey(Window, GLFW_KEY_Q))
		InputManager.KeyPressed(InputCodes::q);
	if (glfwGetKey(Window, GLFW_KEY_R))
		InputManager.KeyPressed(InputCodes::R);
	if (glfwGetKey(Window, GLFW_KEY_S))
		InputManager.KeyPressed(InputCodes::s);
	if (glfwGetKey(Window, GLFW_KEY_T))
		InputManager.KeyPressed(InputCodes::t);
	if (glfwGetKey(Window, GLFW_KEY_U))
		InputManager.KeyPressed(InputCodes::u);
	if (glfwGetKey(Window, GLFW_KEY_V))
		InputManager.KeyPressed(InputCodes::v);
	if (glfwGetKey(Window, GLFW_KEY_W))
		InputManager.KeyPressed(InputCodes::w);
	if (glfwGetKey(Window, GLFW_KEY_X))
		InputManager.KeyPressed(InputCodes::x);
	if (glfwGetKey(Window, GLFW_KEY_Y))
		InputManager.KeyPressed(InputCodes::y);
	if (glfwGetKey(Window, GLFW_KEY_Z))
		InputManager.KeyPressed(InputCodes::z);
	// Set the window's cursor position back to 0,0 (top left corner) so we keep getting a delta
   // glfwSetCursorPos(Window, 0, 0);

	// Poll the input events to see if the user quit or closed the window
	glfwPollEvents();

	// Return the value passed in to tell the game loop that we should continue or not
	return continueGame;
}
//
//  GLFWManager.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__GLFWManager__
#define __OpenGL__GLFWManager__

#include <stdio.h>
#include <string>
#include <GL/glew.h>

// GLEW
#include <GLFW/glfw3.h>
#include "Inputmanager.h"


class GLFWManager
{
public:

	// Create an empty constructor and have the deconstructor release our memory
	GLFWManager() { }
	~GLFWManager() { Destroy(); }


	// This initialized the window and creates the OpenGL context
	int Initialize(unsigned int *width, unsigned int *height, std::string strTitle, bool bFullScreen = false, bool core = true);

	// This swaps the backbuffer to the front and should be called every frame
	void SwapTheBuffers();

	// This processes any needed input for the application, like the Escape key
	bool ProcessInput(bool continueGame);

	// This destroys the window and OpenGL context
	virtual void Destroy();

	virtual InputManager *GetInputManager() { return &InputManager; }

	const GLFWwindow* getWindow();


protected:
	// We created a variable to an InputManager to control camera movements
	InputManager InputManager;

	// This is the GLFW window object that manages the window and input
	GLFWwindow* Window;
};

#endif /* defined(__OpenGL__GLFWManager__) */

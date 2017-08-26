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

class Camera;

class GLFWManager
{
public:

	GLFWManager(Camera* c);

	~GLFWManager();

	int                     Initialize(unsigned int *width, unsigned int *height, std::string strTitle,
                                   bool bFullScreen = false, bool core = true);

	void                    SwapTheBuffers();

	bool                    ProcessInput(bool continueGame);

    Camera*                 GetCamera(void)const;

	virtual void            Destroy();

	virtual InputManager *  GetInputManager() { return &_inputManager; }

	const GLFWwindow*       GetWindow();

private:
    
protected:

	InputManager            _inputManager;

	GLFWwindow*             _window;

    Camera *                _camera;
};

#endif /* defined(__OpenGL__GLFWManager__) */

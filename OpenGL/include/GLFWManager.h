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

template class CameraEx<float>;

class GLFWManager
{
public:

	GLFWManager(CameraEx<float>* c);

	~GLFWManager();

	int                     Initialize(unsigned int *width, unsigned int *height, std::string strTitle,
                                   bool bFullScreen = false, bool core = true);

	void                    SwapTheBuffers();

	bool                    ProcessInput(bool continueGame);

    CameraEx<float>*        GetCamera(void)const;

	virtual void            Destroy();

	const GLFWwindow*       GetWindow();

private:
    
protected:

	GLFWwindow*             _window;

    CameraEx<float> *       _camera;
};

#endif /* defined(__OpenGL__GLFWManager__) */

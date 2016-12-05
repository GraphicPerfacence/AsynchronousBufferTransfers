//
//  GLApplication.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__GLApplication__
#define __OpenGL__GLApplication__

#include <stdio.h>

#include "GLFWManager.h"

class Camera;
class Scene;

class GLApplication
{
public:

	// Create a default constructor and deconstructor which cleans up
	GLApplication(bool isFullScreen = false);

	~GLApplication() { Destroy(); }

	//set application width and hight
	void setApplication(unsigned int w,unsigned int h);

	// This is the main function for our application, which is called by the main() function
	// in the WindowManager.cpp file.  This helps abstract out the environments entry point.
	int GLMain();

	// This gets and sets the window manager for the application.  This should be set right
	// after the GLApplication is created in the main() function.
	GLFWManager *GetWindowManager() { return WindowManager; }
	void SetWindowManager(GLFWManager *pWindowManager) { WindowManager = pWindowManager; }

	// We now pass in a Camera object to our application
	Camera *GetCamera() { return Camera; }
	void SetCamera(Camera *pCamera) { Camera = pCamera; }

	// This initializes the application
	void Initialize();

	// This runs the game loop and only quits when the user hits Escape or closes the window
	void GameLoop();

	// This cleans up the application and tells other objects to also cleanup
	void Destroy();

	void initScene();

private:
	void openglInit(void);
protected:

	GLFWManager *WindowManager;
	Camera *Camera;

	Scene  * _scene;

	unsigned int _width;
	unsigned int _hight;

	bool   _isFullScreen;
};


#endif /* defined(__OpenGL__GLApplication__) */

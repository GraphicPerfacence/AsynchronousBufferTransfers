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
class Audo;

class GLApplication
{
public:


	GLApplication(bool isFullScreen = false);

	~GLApplication() { Destroy(); }


	void            SetApplication(unsigned int w,unsigned int h);

	int             GLMain();

	GLFWManager *   GetWindowManager()const;
	void            SetWindowManager(GLFWManager *pWindowManager);

    Camera *        GetCamera()const;

	void            Initialize();

	void            GameLoop();

    bool            ShouldClose()const;

    void            PressEvents();

    void            Update();

    void            CloseWindow();

    void            Destroy();

  
	void            InitScene();

private:
	void            OpenglInit(void);
    
    void            InitCamera(int,int);
protected:

	GLFWManager *   _windowManager;

	Scene  *        _scene;

    Audo*           _audo;
    
	unsigned int    _width;
	unsigned int    _hight;
	bool            _isFullScreen;
};


#endif /* defined(__OpenGL__GLApplication__) */

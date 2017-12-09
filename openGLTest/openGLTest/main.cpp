//
//  main.cpp
//  openGLTest
//
//  Created by xt on 15/9/27.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include <iostream>



#include "GLFWManager.h"
#include "GLApplication.h"



int main(void)
{
    
    // First create our desired WindowManager implementation so we can set it below
    GLFWManager *pWindowManager = new GLFWManager();
    
    Camera *pCamera = new Camera();
    
    GLApplication application;
    application.SetWindowManager(pWindowManager);
    
    application.SetCamera(pCamera);
    pWindowManager->GetInputManager()->SetCamera(pCamera);
    
    return application.GLMain();
    
}


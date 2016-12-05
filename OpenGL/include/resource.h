

//
//  resource.h
//  OpenGL
//
//  Created by xt on 15/10/25.
//  Copyright (c) 2015年 xt. All rights reserved.
//


#ifndef __OpenGL__Resource__
#define __OpenGL__Resource__


#include <string>
#include "sys.h"
//obj



#if defined X_OS_MACX || defined X_OS_MACX
std::string modelsAndImgBasePath = "/Users/glp/Documents/modelsAndImgs/";
std::string shaderBasePath = "/Users/glp/Documents/projects/OpenGL/OpenGL/shader/";
#elif defined X_OS_WIN32 || defined X_OS_WIN64
std::string modelsAndImgBasePath = "D:/githubPro/opengl/OpenGL/OpenGL/opengl/resourse/";
std::string shaderBasePath = "D:/githubPro/opengl/OpenGL/OpenGL/opengl/../shader/";
#endif 


//texture
std::string textureBasePath = modelsAndImgBasePath + "textures/";
std::string objsBasePath = modelsAndImgBasePath + "objs/";
/////// base Shader //////////////////////


#endif
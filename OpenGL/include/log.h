//
//  log.h
//  OpenGL
//
//  Created by xt on 15/9/8.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__log__
#define __OpenGL__log__

#include <fstream>
#include <gl/glew.h>
#include "comm.h"

class Log
{

private:
	static Log* pInstance; 
	Log();
public:

	static int printOglError(char *file, int line);

	//just print error
	static void printMessage(const char*message);

	//shader error
	static void printShaderInfoLog(unsigned int shader);

	static bool checkFrameBuffer();

	static Log* Instance();

	//void Destroy();
	static void Destroy();

	static std::ofstream out_stream;
};

inline std::string getErrorString(const GLenum err)
{
    return toString(gluErrorString(err));
}

//check

bool CheckFrameBuffer();

void CheckGLError(char* file,int line);

#define CHECK_GL_ERROR() CheckForGLError(__FILE__, __LINE__)
#endif
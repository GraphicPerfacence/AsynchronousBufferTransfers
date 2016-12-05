//
//  comm.cpp
//  OpenGL
//
//  Created by xt on 15/7/24.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/log.h"
#include "../include/comm.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include <string>
#include <sstream>


float stringToFloat(const std::string &source) 
{
	std::stringstream ss(source.c_str());
	float result;
	ss >> result;
	return result;
}

unsigned int stringToUint(const std::string &source) 
{
	std::stringstream ss(source.c_str());
	unsigned int result;
	ss >> result;
	return result;
}

int stringToInt(const std::string &source)
{
	std::stringstream ss(source.c_str());
	int result;
	ss >> result;
	return result;
}

void testOpenGl()
{
	initGlew();
	const GLubyte * byte = glGetString(GL_VERSION);


	GLint manVersion = 0;
	GLint minVersion = 0;


	glGetIntegerv(GL_MAJOR_VERSION, &manVersion);
	glGetIntegerv(GL_MINOR_VERSION, &minVersion);

	printf("openGL manjorVersion :%s \n" , manVersion);
	printf("openGL minjorVersion :%s \n" , minVersion );
	printf("Vendor: %s \n", glGetString(GL_VENDOR));
	printf("Render Name (GPU Name): %s \n", glGetString(GL_RENDERER));

	GLint numEx = 0;
	glGetIntegerv(GL_NUM_EXTENSIONS, &numEx);
	for (GLuint i = 0; i < numEx; i++)
	{
		printf("Extension :%d : %s \n", i, glGetStringi(GL_EXTENSIONS, i));
	}
}

bool initGlew()
{
	if (isGlewInit) return true;

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::Instance()->printMessage( "glew init error ");
		return  false;
	}
	isGlewInit = true;
	return  true;
}

bool initGlfw(bool flag)
{
	if (!glfwInit())
	{
		Log::Instance()->printMessage("glfw init error ");
		return false;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);

	if (flag)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}
	// glfwWindowHint(GLFW_DOUBLEBUFFER, GL_TRUE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	return true;
}

 




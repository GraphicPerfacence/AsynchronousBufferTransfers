
#include "../include/sys.h"
#include "../include/log.h"
#include "../include/base/Execption.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>


#if defined X_OS_WIN32 || defined X_OS_WIN64
#pragma comment (lib, "glu32.lib")     /* link with OpenGL Utility lib */
#endif

std::ofstream Log::out_stream = std::ofstream();

Log* Log::pInstance = NULL;

Log::Log()
{
#if defined X_OS_WIN32 || defined X_OS_WIN64
	out_stream.open("e:/log.txt");
#elif __APPLE__
	out_stream.open("/Users/glp/Documents/projects/OpenGL/log.txt");
#endif
}


int Log::printOglError(char *file, int line)
{
	GLenum glErr;
	int    retCode = 0;

	glErr = glGetError();
	while (glErr != GL_NO_ERROR)
	{
		char buffer[128];
		sprintf(buffer,"glError in file %s @ line %d: %s\n", file, line, gluErrorString(glErr));
		out_stream << buffer;
		retCode = 1;
		glErr = glGetError();
	}
	return retCode;
}

void Log::printMessage(const char*message)
{
	GLenum glErr;
	glErr = glGetError();		

	char buffer[128];

	if (glErr != GL_NO_ERROR)
		sprintf(buffer, "Error XXX :%s \n %s ", message, gluErrorString(glErr));
	else
		sprintf(buffer,"Message :%s \n ", message);

	out_stream << buffer;
}

void Log::printShaderInfoLog(unsigned int shader)
{
	int infologLength = 0;
	int charsWritten = 0;
	GLchar * infoLog;
	printOglError(__FILE__, __LINE__);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infologLength);
	printOglError(__FILE__, __LINE__);

	if (infologLength > 0)
	{
		infoLog = (GLchar*)malloc(infologLength);
		if (infoLog == NULL)
		{
			printf("ERROR: Could not allocate InfoLog buffer\n");
			exit(1);
		}
		glGetShaderInfoLog(shader, infologLength, &charsWritten, infoLog);
		printf("Shader InfoLog:\n%s\n\n", infoLog);
		free(infoLog);
	}
	printOglError(__FILE__, __LINE__);
}

Log* Log::Instance()
{
	if (NULL == pInstance)
	{
		pInstance = new Log();
	}
	return pInstance;

}

void Log::Destroy()
{
	out_stream.close();
	
	delete pInstance;
	pInstance = NULL;
	
	
}

bool CheckFrameBuffer()
{
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch(result)
	{
	case  GL_FRAMEBUFFER_UNDEFINED :
        throw GLException("Framebuffer incomplete, framebuffer undefinded");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
        throw GLException("Framebuffer incomplete, framebuffer completness not satisfied");
		return false;
    case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
        throw GLException("Framebuffer incomplete, attached images must have same dimensions");
        break;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
        throw GLException("Framebuffer incomplete, no attachment");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER :
        throw GLException("Framebuffer incomplete, readBuffer states reading buffer that is not attached to fbo");
		return false;
	case  GL_FRAMEBUFFER_UNSUPPORTED :
        throw GLException("Unsupported framebuffer format (implementation dependent)");
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE :
        throw GLException("framebuffer  multisisample");
		return false;
	case  GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
        throw GLException("framebuffer  LAYER TARGETS");
		return false;
	}

	return true;
}


void CheckGLError(char* file,int line)
{
    GLenum glErr;
    while((glErr = glGetError()) != GL_NO_ERROR) {
        std::string msg("GL Error:");
        msg += (glErr);
        msg += '(';
        msg += getErrorString(glErr);
        msg += ")  in File ";
        msg += file;
        msg += " at line: ";
        msg += (line);
        msg += '\n';
        throw GLException(msg);
    }

}

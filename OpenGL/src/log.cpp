
#include "../include/sys.h"
#include "../include/log.h"


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
	out_stream.open("/Users/glp/Documents/projects/OpenGL/log");
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

bool Log::glError(void)
{
	GLenum glErr;
	int    retCode = 0;

	char * error = "no error";
	glErr = glGetError();
	if(glErr != GL_NO_ERROR)
	{
		 switch(glErr)
		 {
		 case GL_INVALID_ENUM:
			 error = "An unacceptable value is specified for an enumerated argument";
			 break;
		 case GL_INVALID_VALUE:
			 error = "A numeric argument is out of range";
			 break;
		 case GL_INVALID_OPERATION:
			 error = "The specified operation is not allowed in the current state.";
			 break;
		 case GL_INVALID_FRAMEBUFFER_OPERATION:
			 error = "The framebuffer object is not complete";
			 break;
		 case GL_OUT_OF_MEMORY:
			 error = "There is not enough memory left to execute the command";
			 break;
		 case GL_STACK_UNDERFLOW:
			 error = "internal stack to underflow";
			 break;
		 case GL_STACK_OVERFLOW:
			 error = " internal stack to overflow";
			 break;
		 }

		 return false;
	}
	
	return true;
}

bool Log::checkFrameBuffer()
{
	GLenum result = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	switch(result)
	{
	case  GL_FRAMEBUFFER_UNDEFINED :
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT :
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT :
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER :
		return false;
	case  GL_FRAMEBUFFER_UNSUPPORTED :
		return false;
	case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE :
		return false;
	case  GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS :
		return false;
	}

	return true;
}

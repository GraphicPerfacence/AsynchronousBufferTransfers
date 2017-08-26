
#include "../include/XGLQuery.h"

GLfloat XGLQuery::getCurrentTime()
{
	GLint64 timer;
	glGetInteger64v(GL_TIMESTAMP,&timer);

	//milliseconds
	return timer / 1000000.0;
}

XGLQuery::XGLQuery()
{
	queryBackBuffer = 0;
	queryFrontBuffer = 1;
}

void XGLQuery::genQueries()
{
	glGenQueries(1,queryID[queryBackBuffer]);
	glGenQueries(1,queryID[queryFrontBuffer]);

	// dummy query to prevent OpenGL errors from popping out
	glQueryCounter(queryID[queryFrontBuffer][0], GL_TIMESTAMP);
}

void XGLQuery::swapQueryBuffers()
{
	if (queryBackBuffer) 
	{
		queryBackBuffer = 0;
		queryFrontBuffer = 1;
	}
	else 
	{
		queryBackBuffer = 1;
		queryFrontBuffer = 0;
	}
}

void XGLQuery::begin()
{
	glBeginQuery(GL_TIME_ELAPSED,queryID[queryBackBuffer][0]);
}

void XGLQuery::end()
{
	glEndQuery(GL_TIME_ELAPSED);
}

GLuint64 XGLQuery::time()
{
	GLuint64 timer;
	glGetQueryObjectui64v(queryID[queryFrontBuffer][0],GL_QUERY_RESULT,&timer);

	return timer / 1000000.0;
}

void XGLQuery::deleteQuery()
{
	glDeleteQueries(1,queryID[queryBackBuffer]);
	glDeleteQueries(1,queryID[queryFrontBuffer]);
}

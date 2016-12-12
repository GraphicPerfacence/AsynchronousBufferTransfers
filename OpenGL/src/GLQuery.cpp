
#include "../include/GLQuery.h"

GLfloat GLQuery::getCurrentTime()
{
	GLint64 timer;
	glGetInteger64v(GL_TIMESTAMP,&timer);

	//milliseconds
	return timer / 1000000.0;
}

GLQuery::GLQuery()
{
	queryBackBuffer = 0;
	queryFrontBuffer = 1;
}

void GLQuery::genQueries()
{
	glGenQueries(1,queryID[queryBackBuffer]);
	glGenQueries(1,queryID[queryFrontBuffer]);

	// dummy query to prevent OpenGL errors from popping out
	glQueryCounter(queryID[queryFrontBuffer][0], GL_TIMESTAMP);
}

void GLQuery::swapQueryBuffers()
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

void GLQuery::begin()
{
	glBeginQuery(GL_TIME_ELAPSED,queryID[queryBackBuffer][0]);
}

void GLQuery::end()
{
	glEndQuery(GL_TIME_ELAPSED);
}

GLuint64 GLQuery::time()
{
	GLint done = false;

	while (!done) {
		glGetQueryObjectiv(queryID[queryBackBuffer][0],
			GL_QUERY_RESULT_AVAILABLE,
			&done);
	}

	// get the query result
	
	GLuint64 timer;
	glGetQueryObjectui64v(queryID[queryBackBuffer][0],GL_QUERY_RESULT,&timer);

	return timer / 1000000.0;
}

void GLQuery::deleteQuery()
{
	glDeleteQueries(1,queryID[queryBackBuffer]);
	glDeleteQueries(1,queryID[queryFrontBuffer]);
}

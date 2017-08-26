

#include <gl/glew.h>


class XGLQuery
{
public:
	static GLfloat getCurrentTime();

	XGLQuery();

	void genQueries();

	void swapQueryBuffers();

	void begin();
	void end();

	//Milliseconds
	GLuint64 time();

	void deleteQuery();

private:
	unsigned int queryID[2][1];
	unsigned int queryBackBuffer;
	unsigned int queryFrontBuffer;
};
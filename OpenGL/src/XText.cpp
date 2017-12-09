
#include "XText.h"
#include "shader.hpp"


#include <gl/glew.h>

XText::XText()
{
    
}

XText::~XText()
{
	if(_shader)
	{
		delete _shader;
		_shader = NULL;
	}
}

bool XText::init(void)
{
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0); 

	initShader();

	return true;
}



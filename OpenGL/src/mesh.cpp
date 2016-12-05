

#include "../include/mesh.h"
#include "../include/ReadFile.h"
#include "../include/shader.hpp"
#include "../include/log.h"

#include <stddef.h> 
#include <gl/glew.h>
#include <iostream>
#include <sstream>
#include <map>


Mesh::~Mesh()
{
	destory();
}

void Mesh::destory(void)
{
	if (_VBOID)
	{
		glDeleteBuffers(1, &_VBOID);
		_VBOID = 0;
	}
	if (_IBOID)
	{
		glDeleteBuffers(1, &_IBOID);
		_IBOID = 0;
	}
	if (_VAOID)
	{
		glBindVertexArray(0);
		glDeleteVertexArrays(1, &_VAOID);
		_VAOID = 0;
	}
}

void Mesh::draw(const Shader*shader)const
{
	
	// Bind appropriate textures
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;

	std::map<unsigned int ,bool> testHaveTextures;

	for(GLuint i = 0; i < _textures.size(); i++)
	{
		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = _textures[i].type;
		if(name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if(name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		else if(name == "texture_normal")
			ss << normalNr++; // Transfer GLuint to stream
		else if(name == "texture_height")
			ss << heightNr++; // Transfer GLuint to stream
		number = ss.str(); 
		// Now set the sampler to the correct texture unit
		int lo =  shader->GetVariable((name + number).c_str());
		if(lo != -1)
		{
			glActiveTexture(GL_TEXTURE0 + i); // Active proper texture unit before binding
			shader->SetInt(lo,i);
			// And finally bind the texture
			glBindTexture(GL_TEXTURE_2D, _textures[i].id);

			testHaveTextures[i] = true;
		}
		else
		{
			testHaveTextures[i] = false;
		}
	}

	// Draw mesh
	glBindVertexArray(_VAOID);
	 
	if(Log::Instance()->glError())
	{
		glDrawElements(GL_TRIANGLES, _indicesCount, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	for (GLuint i = 0; i < _textures.size(); i++)
	{
		if(testHaveTextures[i])
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}

void Mesh::setupMesh(std::vector<VertexFormat>&vs,std::vector<unsigned int >&ic,std::vector<TextureR>&ts)
{
	/*_vertexs = vs;
	_elementIndices = ic;*/
	_textures = ts;

	_indicesCount = ic.size();

	// Create buffers/arrays
	glGenVertexArrays(1, &_VAOID);
 
	glGenBuffers(1, &_VBOID);
	glGenBuffers(1, &_IBOID);

	glBindVertexArray(_VAOID);
	glBindBuffer(GL_ARRAY_BUFFER, _VBOID);

	glBufferData(GL_ARRAY_BUFFER, vs.size() * sizeof(VertexFormat), &vs[0], GL_STATIC_DRAW);  

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBOID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, ic.size() * sizeof(GLuint), &ic[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)0);
	// Vertex Normals
	glEnableVertexAttribArray(1);	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, normal_x));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);	
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, texcoord_x));
	// Vertex Tangent
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, tangent_x));
	// Vertex Bitangent
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (GLvoid*)offsetof(VertexFormat, bitangent_x));

	glBindVertexArray(0);
}

void Mesh::setupMesh(void)
{
	setupMesh(_vertexs,_elementIndices,_textures);
}

Mesh::Mesh()
{
}

bool INode::initMesh(const char* fileName,unsigned int steps)
{
	//return loadOBJ(fileName, _VAOID, _VBOID, _IBOID, _indicesCount);
	return loadObjByAssimp(fileName,_meshs,steps);
}

//aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace
INode::INode(const char*fileName,unsigned int  steps)
{
	initMesh(fileName,steps);
}

void INode::drawNode(const Shader*shader)
{
	for (unsigned int i = 0;i < _meshs.size();i++)
	{
		_meshs[i].draw(shader);
	}
}

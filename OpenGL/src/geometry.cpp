#include "../include/geometry.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>			// Used for the GLM math library
#include <glm/gtx/transform2.hpp>



void initPoints(GLuint& pointVAO)
{
	GLfloat pointsVertices[] =
	{
		-0.5,-0.5,0.5,
		0.5,-0.5,-0.5,
		0.5,0.5,-0.5,
		-0.5,0.5,0.5
	};

	glGenVertexArrays(1, &pointVAO);
	glBindVertexArray(pointVAO);

	GLuint pointVBO;
	glGenBuffers(1, &pointVBO);
	glBindBuffer(GL_ARRAY_BUFFER, pointVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pointsVertices), &pointsVertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
void drawPoints(GLuint& pointVAO)
{
	glBindVertexArray(pointVAO);
	glDrawArrays(GL_POINTS, 0, 4);
	glBindVertexArray(0);
}



void initQuad(GLuint &QVAO)
{
	GLfloat planeVertices[] = {
		// Positions            // Normals           // Texture Coords
		25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 0.0f,
		-25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  25.0f,
		-25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,

		25.0f, -0.5f,  25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 0.0f,
		25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  25.0f, 25.0f,
		-25.0f, -0.5f, -25.0f,  0.0f,  1.0f,  0.0f,  0.0f,  25.0f
	};
	// Setup plane VAO
	GLuint planeVBO;
	glGenVertexArrays(1, &QVAO);
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(QVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindVertexArray(0);

}
void drawQuad(GLuint& QVAO)
{
	glBindVertexArray(QVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

void initCub(GLuint&cubeVAO)
{
	GLfloat vertices[] = {
		// Back face
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, // Bottom-left
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,  // top-right
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  // bottom-left
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,// top-left
		// Front face
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom-left
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,  // bottom-right
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,  // top-right
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // top-right
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // top-left
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // bottom-left
		// Left face
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-left
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-left
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,  // bottom-right
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-right
		// Right face
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, // top-left
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // bottom-right
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top-right         
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,  // bottom-right
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,  // top-left
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, // bottom-left     
		// Bottom face
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, // top-left
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,// bottom-left
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f, // bottom-left
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, // bottom-right
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f, // top-right
		// Top face
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // top-right     
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom-right
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,// top-left
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f // bottom-left          
	};
	glGenVertexArrays(1, &cubeVAO);
	GLuint cubeVBO;
	glGenBuffers(1, &cubeVBO);
	// Fill buffer
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Link vertex attributes
	glBindVertexArray(cubeVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void drawCub(GLuint&cubeVAO, bool instance, GLuint num)
{
	if (!instance)
	{
		glBindVertexArray(cubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
	}
	else
	{
		glBindVertexArray(cubeVAO);
		glDrawArraysInstanced(GL_TRIANGLES, 0, 36, num);
		glBindVertexArray(0);
	}

}

void initSkyBox(GLuint &skyboxVAO)
{
	GLfloat skyboxVertices[] = {
		// Positions          
	   -1.0f, 1.0f, -1.0f,
	   -1.0f, -1.0f, -1.0f,
	   1.0f, -1.0f, -1.0f,
	   1.0f, -1.0f, -1.0f,
	   1.0f, 1.0f, -1.0f,
	   -1.0f, 1.0f, -1.0f,

	   -1.0f, -1.0f, 1.0f,
	   -1.0f, -1.0f, -1.0f,
	   -1.0f, 1.0f, -1.0f,
	   -1.0f, 1.0f, -1.0f,
	   -1.0f, 1.0f, 1.0f,
	   -1.0f, -1.0f, 1.0f,

	   1.0f, -1.0f, -1.0f,
	   1.0f, -1.0f, 1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f, 1.0f, -1.0f,
	   1.0f, -1.0f, -1.0f,

	   -1.0f, -1.0f, 1.0f,
	   -1.0f, 1.0f, 1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f, -1.0f, 1.0f,
	   -1.0f, -1.0f, 1.0f,

	   -1.0f, 1.0f, -1.0f,
	   1.0f, 1.0f, -1.0f,
	   1.0f, 1.0f, 1.0f,
	   1.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, 1.0f,
	   -1.0f, 1.0f, -1.0f,

	   -1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f, 1.0f,
	   1.0f, -1.0f, -1.0f,
	   1.0f, -1.0f, -1.0f,
	   -1.0f, -1.0f, 1.0f,
	   1.0f, -1.0f, 1.0f
	};

	GLuint skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);
}

void drawSkyBox(GLuint& skyboxVAO)
{
	glBindVertexArray(skyboxVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}

Matrix * instanceGeomModeMatrix(unsigned int amount)
{
	Matrix *modelMatrices = new glm::mat4[amount];
	srand(glfwGetTime()); // initialize random seed

	GLfloat radius = 5.0f;
	GLfloat offset = 1.0f;
	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		// 1. Translation: Randomly displace along circle with radius 'radius' in range [-offset, offset]
		GLfloat angle = (GLfloat)i / (GLfloat)amount * 360.0f;
		GLfloat displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat x = sin(angle) * radius + displacement;
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat y = -2.5f + displacement * 0.4f; // Keep height of asteroid field smaller compared to width of x and z
		displacement = (rand() % (GLint)(2 * offset * 100)) / 100.0f - offset;
		GLfloat z = cos(angle) * radius + displacement;
		model = glm::translate(model, glm::vec3(x, 0.1, z));

		// 2. Scale: Scale between 0.05 and 0.25f
		//GLfloat scale = (rand() % 20) / 100.0f + 0.05;
		//model = glm::scale(model, glm::vec3(scale));

		// 3. Rotation: add random rotation around a (semi)randomly picked rotation axis vector
		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		// 4. Now add to list of matrices
		modelMatrices[i] = model;
	}

	return modelMatrices;
}


void postAddInstanceModelMatrix(GLuint index, GLuint num, const glm::mat4* modes)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, num * sizeof(glm::mat4), &modes[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(0));
	glEnableVertexAttribArray(index + 1);
	glVertexAttribPointer(index + 1, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(1 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(index + 2);
	glVertexAttribPointer(index + 2, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(index + 3);
	glVertexAttribPointer(index + 3, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(glm::vec4), (GLvoid*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(index, 1);
	glVertexAttribDivisor(index + 1, 1);
	glVertexAttribDivisor(index + 2, 1);
	glVertexAttribDivisor(index + 3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void initQuadWithNormal(GLuint&QVAO)
{
	glm::vec3 pos1(-1.0, 1.0, 0.0);
	glm::vec3 pos2(-1.0, -1.0, 0.0);
	glm::vec3 pos3(1.0, -1.0, 0.0);
	glm::vec3 pos4(1.0, 1.0, 0.0);
	// texture coordinates
	glm::vec2 uv1(0.0, 1.0);
	glm::vec2 uv2(0.0, 0.0);
	glm::vec2 uv3(1.0, 0.0);
	glm::vec2 uv4(1.0, 1.0);
	// normal vector
	glm::vec3 nm(0.0, 0.0, 1.0);
	
	// calculate tangent/bitangent vectors of both triangles
	glm::vec3 tangent1, bitangent1;
	glm::vec3 tangent2, bitangent2;
	// - triangle 1
	glm::vec3 edge1 = pos2 - pos1;
	glm::vec3 edge2 = pos3 - pos1;
	glm::vec2 deltaUV1 = uv2 - uv1;
	glm::vec2 deltaUV2 = uv3 - uv1;
	
	GLfloat f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	
	tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent1 = glm::normalize(tangent1);
	
	bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent1 = glm::normalize(bitangent1);
	
	// - triangle 2
	edge1 = pos3 - pos1;
	edge2 = pos4 - pos1;
	deltaUV1 = uv3 - uv1;
	deltaUV2 = uv4 - uv1;
	
	f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);
	
	tangent2.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
	tangent2.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
	tangent2.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
	tangent2 = glm::normalize(tangent2);
	
	
	bitangent2.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
	bitangent2.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
	bitangent2.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
	bitangent2 = glm::normalize(bitangent2);
	
	
	GLfloat quadVertices[] = {
		// Positions            // normal         // TexCoords  // Tangent                          // Bitangent
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos2.x, pos2.y, pos2.z, nm.x, nm.y, nm.z, uv2.x, uv2.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent1.x, tangent1.y, tangent1.z, bitangent1.x, bitangent1.y, bitangent1.z,
		
		pos1.x, pos1.y, pos1.z, nm.x, nm.y, nm.z, uv1.x, uv1.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos3.x, pos3.y, pos3.z, nm.x, nm.y, nm.z, uv3.x, uv3.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z,
		pos4.x, pos4.y, pos4.z, nm.x, nm.y, nm.z, uv4.x, uv4.y, tangent2.x, tangent2.y, tangent2.z, bitangent2.x, bitangent2.y, bitangent2.z
	};
	// Setup plane VAO
	glGenVertexArrays(1, &QVAO);
	GLuint planeVBO;
	glGenBuffers(1, &planeVBO);
	glBindVertexArray(QVAO);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 14 * sizeof(GLfloat), (GLvoid*)(11 * sizeof(GLfloat)));
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindVertexArray(0);
	
}
void drawQuadWithNormal(GLuint&QVAO)
{
	glBindVertexArray(QVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}
void initScreenQuad(GLuint&screenQuad)
{
	GLfloat planeVertices[] = {
		// Positions                    // Texture Coords
		-1.0f,  1.0f, 0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f,  0.0f, 0.0f,
		1.0f,  1.0f, 0.0f,  1.0f, 1.0f,
		1.0f, -1.0f, 0.0f,  1.0f, 0.0f,
	};
	// Setup plane VAO
	GLuint planeVBO;
	glGenVertexArrays(1, &screenQuad);
	glGenBuffers(1, &planeVBO);

	glBindVertexArray(screenQuad);
	glBindBuffer(GL_ARRAY_BUFFER, planeVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	
	glBindVertexArray(0);
}

void drawScreenQuad(GLuint&screenQuad)
{
	glBindVertexArray(screenQuad);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

void initTorus(TriangleBatch & torusBatch, GLfloat majorRadius, GLfloat minorRadius, GLint numMajor, GLint numMinor)
{
	double majorStep = 2.0f*M3D_PI / numMajor;
	double minorStep = 2.0f*M3D_PI / numMinor;
	int i, j;

	torusBatch.BeginMesh(numMajor * (numMinor + 1) * 6);
	for (i = 0; i < numMajor; ++i)
	{
		double a0 = i * majorStep;
		double a1 = a0 + majorStep;
		GLfloat x0 = (GLfloat)cos(a0);
		GLfloat y0 = (GLfloat)sin(a0);
		GLfloat x1 = (GLfloat)cos(a1);
		GLfloat y1 = (GLfloat)sin(a1);

		Vec3f vVertex[4];
		Vec3f vNormal[4];
		Vec2f vTexture[4];

		for (j = 0; j <= numMinor; ++j)
		{
			double b = j * minorStep;
			GLfloat c = (GLfloat)cos(b);
			GLfloat r = minorRadius * c + majorRadius;
			GLfloat z = minorRadius * (GLfloat)sin(b);

			// First point
			vTexture[0][0] = (float)(i) / (float)(numMajor);
			vTexture[0][1] = (float)(j) / (float)(numMinor);
			vNormal[0][0] = x0*c;
			vNormal[0][1] = y0*c;
			vNormal[0][2] = z / minorRadius;
			m3dNormalizeVector3(vNormal[0]);
			vVertex[0][0] = x0 * r;
			vVertex[0][1] = y0 * r;
			vVertex[0][2] = z;

			// Second point
			vTexture[1][0] = (float)(i + 1) / (float)(numMajor);
			vTexture[1][1] = (float)(j) / (float)(numMinor);
			vNormal[1][0] = x1*c;
			vNormal[1][1] = y1*c;
			vNormal[1][2] = z / minorRadius;
			m3dNormalizeVector3(vNormal[1]);
			vVertex[1][0] = x1*r;
			vVertex[1][1] = y1*r;
			vVertex[1][2] = z;

			// Next one over
			b = (j + 1) * minorStep;
			c = (GLfloat)cos(b);
			r = minorRadius * c + majorRadius;
			z = minorRadius * (GLfloat)sin(b);

			// Third (based on first)
			vTexture[2][0] = (float)(i) / (float)(numMajor);
			vTexture[2][1] = (float)(j + 1) / (float)(numMinor);
			vNormal[2][0] = x0*c;
			vNormal[2][1] = y0*c;
			vNormal[2][2] = z / minorRadius;
			m3dNormalizeVector3(vNormal[2]);
			vVertex[2][0] = x0 * r;
			vVertex[2][1] = y0 * r;
			vVertex[2][2] = z;

			// Fourth (based on second)
			vTexture[3][0] = (float)(i + 1) / (float)(numMajor);
			vTexture[3][1] = (float)(j + 1) / (float)(numMinor);
			vNormal[3][0] = x1*c;
			vNormal[3][1] = y1*c;
			vNormal[3][2] = z / minorRadius;
			m3dNormalizeVector3(vNormal[3]);
			vVertex[3][0] = x1*r;
			vVertex[3][1] = y1*r;
			vVertex[3][2] = z;

			torusBatch.AddTriangle(vVertex, vNormal, vTexture);

			// Rearrange for next triangle
			vVertex[0].x = vVertex[1].x;
			vVertex[0].y = vVertex[1].y;
			vVertex[0].z = vVertex[1].z;

			vNormal[0].x = vNormal[1].x;
			vNormal[0].y = vNormal[1].y;
			vNormal[0].z = vNormal[1].z;

			vTexture[0].s = vTexture[1].s;
			vTexture[0].t = vTexture[1].t;

			vVertex[1].x = vVertex[3].x;
			vVertex[1].y = vVertex[3].y;
			vVertex[1].z = vVertex[3].z;

			vNormal[1].x = vNormal[3].x;
			vNormal[1].y = vNormal[3].y;
			vNormal[0].z = vNormal[3].z;

			vTexture[1].s = vTexture[3].s;
			vTexture[1].t = vTexture[3].t;

			//memcpy(vTexture[0], vTexture[1], sizeof(M3DVector2f));

//memcpy(vVertex[1], vVertex[3], sizeof(M3DVector3f));
//memcpy(vNormal[1], vNormal[3], sizeof(M3DVector3f));
//memcpy(vTexture[1], vTexture[3], sizeof(M3DVector2f));

			torusBatch.AddTriangle(vVertex, vNormal, vTexture);
		}
	}
	torusBatch.End();
}

void generateOrtho2DMat(GLuint screenWidth, GLuint screenHeight,
	Matrix &orthoMatrix, Batch &screenQuad)
{

	float right = (float)screenWidth;
	float left = 0.0f;
	float top = (float)screenHeight;
	float bottom = 0.0f;

	// set ortho matrix
	orthoMatrix[0][0] = (float)(2 / (right - left));
	orthoMatrix[0][1] = 0.0;
	orthoMatrix[0][2] = 0.0;
	orthoMatrix[0][3] = 0.0;

	orthoMatrix[1][0] = 0.0;
	orthoMatrix[1][1] = (float)(2 / (top - bottom));
	orthoMatrix[1][2] = 0.0;
	orthoMatrix[1][3] = 0.0;

	orthoMatrix[2][0] = 0.0;
	orthoMatrix[2][1] = 0.0;
	orthoMatrix[2][2] = (float)(-2 / (1.0 - 0.0));
	orthoMatrix[2][3] = 0.0;

	orthoMatrix[3][0] = -1 * (right + left) / (right - left);
	orthoMatrix[3][1] = -1 * (top + bottom) / (top - bottom);
	orthoMatrix[3][2] = -1.0f;
	orthoMatrix[3][3] = 1.0;

	// set screen quad vertex array
	screenQuad.Reset();
	screenQuad.Begin(GL_TRIANGLE_STRIP, 4, 1);
	screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	screenQuad.MultiTexCoord2f(0, 0.0f, 0.0f);
	screenQuad.Vertex3f(0.0f, 0.0f, 0.0f);

	screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	screenQuad.MultiTexCoord2f(0, 1.0f, 0.0f);
	screenQuad.Vertex3f((float)screenWidth, 0.0f, 0.0f);

	screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	screenQuad.MultiTexCoord2f(0, 0.0f, 1.0f);
	screenQuad.Vertex3f(0.0f, (float)screenHeight, 0.0f);

	screenQuad.Color4f(0.0f, 1.0f, 0.0f, 1.0f);
	screenQuad.MultiTexCoord2f(0, 1.0f, 1.0f);
	screenQuad.Vertex3f((float)screenWidth, (float)screenHeight, 0.0f);
	screenQuad.End();

}
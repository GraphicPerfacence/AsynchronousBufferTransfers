
#include "../include/Batch.h"

#include <stdio.h>
#include <string.h>

#include <gl/glew.h>

Batch::Batch(void) : nNumTextureUnits(0), nNumVerts(0), pVerts(NULL), pNormals(NULL), pColors(NULL), pTexCoords(NULL), uiVertexArray(0),
uiNormalArray(0), uiColorArray(0), vertexArrayObject(0), bBatchDone(false), nVertsBuilding(0), uiTextureCoordArray(NULL)
{
}

Batch::~Batch(void)
{
	// Vertex buffer objects
	if (uiVertexArray != 0)
		glDeleteBuffers(1, &uiVertexArray);

	if (uiNormalArray != 0)
		glDeleteBuffers(1, &uiNormalArray);

	if (uiColorArray != 0)
		glDeleteBuffers(1, &uiColorArray);

	for (unsigned int i = 0; i < nNumTextureUnits; i++)
		glDeleteBuffers(1, &uiTextureCoordArray[i]);

#ifndef OPENGL_ES
	glDeleteVertexArrays(1, &vertexArrayObject);
#endif

	delete[] uiTextureCoordArray;
	delete[] pTexCoords;
}

void Batch::Begin(unsigned int primitive, unsigned int nVerts, unsigned int nTextureUnits)
{
	primitiveType = primitive;
	nNumVerts = nVerts;

	if (nTextureUnits > 4)   nTextureUnits = 4;

	nNumTextureUnits = nTextureUnits;
	if (nNumTextureUnits != 0) {
		uiTextureCoordArray = new unsigned int[nNumTextureUnits];

		// An array of pointers to texture coordinate arrays
		pTexCoords = new Vec2f*[nNumTextureUnits];
		for (unsigned int i = 0; i < nNumTextureUnits; i++) {
			uiTextureCoordArray[i] = 0;
			pTexCoords[i] = NULL;
		}
	}

	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
}

void Batch::CopyVertexData3f(Vec3f *vVerts)
{
	if (uiVertexArray == 0)
	{
		glGenBuffers(1, &uiVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, vVerts, GL_DYNAMIC_DRAW);
	}
	else
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * nNumVerts, vVerts);
		pVerts = NULL;
	}
}

void Batch::CopyNormalDataf(Vec3f *vNorms)
{
	// First time, create the buffer object, allocate the space
	if (uiNormalArray == 0) {
		glGenBuffers(1, &uiNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, vNorms, GL_DYNAMIC_DRAW);
	}
	else {	// Just bind to existing object
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);

		// Copy the data in
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 3 * nNumVerts, vNorms);
		pNormals = NULL;
	}
}

void Batch::CopyColorData4f(Vec4f *vColors)
{
	// First time, create the buffer object, allocate the space
	if (uiColorArray == 0) {
		glGenBuffers(1, &uiColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * nNumVerts, vColors, GL_DYNAMIC_DRAW);
	}
	else {	// Just bind to existing object
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);

		// Copy the data in
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 4 * nNumVerts, vColors);
		pColors = NULL;
	}
}

void Batch::CopyTexCoordData2f(Vec2f *vTexCoords, unsigned int uiTextureLayer)
{
	// First time, create the buffer object, allocate the space
	if (uiTextureCoordArray[uiTextureLayer] == 0) {
		glGenBuffers(1, &uiTextureCoordArray[uiTextureLayer]);
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[uiTextureLayer]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nNumVerts, vTexCoords, GL_DYNAMIC_DRAW);
	}
	else {	// Just bind to existing object
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[uiTextureLayer]);

		// Copy the data in
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 2 * nNumVerts, vTexCoords);
		pTexCoords[uiTextureLayer] = NULL;
	}
}

void Batch::End(void)
{
	if (pVerts != NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		pVerts = NULL;
	}
	if (pColors != NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		pColors = NULL;
	}

	if (pNormals != NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		pNormals = NULL;
	}
	for (unsigned int i = 0; i < nNumTextureUnits; i++)
		if (pTexCoords[i] != NULL)
		{
			glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[i]);
			glUnmapBuffer(GL_ARRAY_BUFFER);
			pTexCoords[i] = NULL;
		}

	glBindVertexArray(vertexArrayObject);
	if (uiVertexArray != 0) {
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (uiColorArray != 0) {
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, 0);
	}

	if (uiNormalArray != 0) {
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	}

	// How many texture units
	for (unsigned int i = 0; i < nNumTextureUnits; i++)
		if (uiTextureCoordArray[i] != 0) {
			glEnableVertexAttribArray(3 + i),
				glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[i]);
			glVertexAttribPointer(3 + i, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
	bBatchDone = true;

	glBindVertexArray(0);
}

void Batch::Reset(void)
{
	bBatchDone = false;
	nVertsBuilding = 0;
}

void Batch::Vertex3f(float x, float y, float z)
{
	if (uiVertexArray == 0)
	{
		glGenBuffers(1, &uiVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}
	if (pVerts == NULL)
	{
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		pVerts = (Vec3f*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	pVerts[nVertsBuilding][0] = x;
	pVerts[nVertsBuilding][1] = y;
	pVerts[nVertsBuilding][2] = z;
	nVertsBuilding++;
}

void Batch::Vertex3fv(Vec3f vVertex)
{
	if (uiVertexArray == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiVertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pVerts == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiVertexArray);
		pVerts = (Vec3f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	//memcpy(pVerts[nVertsBuilding], vVertex, sizeof(M3DVector3f));
	pVerts[nVertsBuilding][0] = vVertex.x;
	pVerts[nVertsBuilding][1] = vVertex.y;
	pVerts[nVertsBuilding][2] = vVertex.z;

	nVertsBuilding++;
}

void Batch::Normal3f(float x, float y, float z)
{
	// First see if the vertex array buffer has been created...
	if (uiNormalArray == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pNormals == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		pNormals = (Vec3f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	pNormals[nVertsBuilding][0] = x;
	pNormals[nVertsBuilding][1] = y;
	pNormals[nVertsBuilding][2] = z;
}

void Batch::Normal3fv(Vec3f vNormal)
{
	// First see if the vertex array buffer has been created...
	if (uiNormalArray == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiNormalArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 3 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pNormals == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiNormalArray);
		pNormals = (Vec3f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	//memcpy(pNormals[nVertsBuilding], vNormal, sizeof(M3DVector3f));
	pNormals[nVertsBuilding][0] = vNormal.x;
	pNormals[nVertsBuilding][1] = vNormal.y;
	pNormals[nVertsBuilding][2] = vNormal.z;

}
void Batch::Color4f(float r, float g, float b, float a)
{
	// First see if the vertex array buffer has been created...
	if (uiColorArray == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pColors == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		pColors = (Vec4f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	pColors[nVertsBuilding][0] = r;
	pColors[nVertsBuilding][1] = g;
	pColors[nVertsBuilding][2] = b;
	pColors[nVertsBuilding][3] = a;
}

void Batch::Color4fv(Vec4f vColor)
{
	// First see if the vertex array buffer has been created...
	if (uiColorArray == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiColorArray);
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pColors == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiColorArray);
		pColors = (Vec4f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	//memcpy(pColors[nVertsBuilding], vColor, sizeof(M3DVector4f));
	pColors[nVertsBuilding][0] = vColor.r;
	pColors[nVertsBuilding][1] = vColor.g;
	pColors[nVertsBuilding][2] = vColor.b;
	pColors[nVertsBuilding][3] = vColor.a;

}

void Batch::MultiTexCoord2f(unsigned int texture, float s, float t)
{
	// First see if the vertex array buffer has been created...
	if (uiTextureCoordArray[texture] == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiTextureCoordArray[texture]);
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[texture]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pTexCoords[texture] == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[texture]);
		pTexCoords[texture] = (Vec2f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	pTexCoords[texture][nVertsBuilding][0] = s;
	pTexCoords[texture][nVertsBuilding][1] = t;
}

// Ditto above  
void Batch::MultiTexCoord2fv(unsigned int texture, Vec2f vTexCoord)
{
	// First see if the vertex array buffer has been created...
	if (uiTextureCoordArray[texture] == 0) {	// Nope, we need to create it
		glGenBuffers(1, &uiTextureCoordArray[texture]);
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[texture]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 2 * nNumVerts, NULL, GL_DYNAMIC_DRAW);
	}

	// Now see if it's already mapped, if not, map it
	if (pTexCoords[texture] == NULL) {
		glBindBuffer(GL_ARRAY_BUFFER, uiTextureCoordArray[texture]);
		pTexCoords[texture] = (Vec2f *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	// Ignore if we go past the end, keeps things from blowing up
	if (nVertsBuilding >= nNumVerts)
		return;

	// Copy it in...
	//memcpy(pTexCoords[texture], vTexCoord, sizeof(M3DVector2f));
	pTexCoords[texture][nVertsBuilding][0] = vTexCoord.s;
	pTexCoords[texture][nVertsBuilding][1] = vTexCoord.t;

}

void Batch::Draw(void)
{
	if (!bBatchDone) return;
	glBindVertexArray(vertexArrayObject);
	glDrawArrays(primitiveType, 0, nNumVerts);
	glBindVertexArray(0);
}
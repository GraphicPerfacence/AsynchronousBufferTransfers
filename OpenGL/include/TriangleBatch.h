
#ifndef __TRIANGLE_BATCH
#define __TRIANGLE_BATCH 

#include "BatchBase.h"

#define VERTEX_DATA     0
#define NORMAL_DATA     1
#define TEXTURE_DATA    2
#define INDEX_DATA      3

class TriangleBatch : public BatchBase
{
public:

	TriangleBatch(void);
	
	virtual ~TriangleBatch(void);

	// Use these three functions to add triangles
	void BeginMesh(unsigned int nMaxVerts);
	void AddTriangle(Vec3f verts[3], Vec3f vNorms[3], Vec2f vTexCoords[3]);
	void End(void);

	// Useful for statistics
	inline unsigned int GetIndexCount(void) { return nNumIndexes; }
	inline unsigned int GetVertexCount(void) { return nNumVerts; }


	// Draw - make sure you call glEnableClientState for these arrays
	virtual void Draw(void);

protected:
	unsigned short	*pIndexes;        // Array of indexes
	Vec3f		*pVerts;        // Array of vertices
	Vec3f		*pNorms;        // Array of normals
	Vec2f		*pTexCoords;    // Array of texture coordinates

	unsigned int nMaxIndexes;         // Maximum workspace
	unsigned int nNumIndexes;         // Number of indexes currently used
	unsigned int nNumVerts;           // Number of vertices actually used

	unsigned int bufferObjects[4];
	unsigned int vertexArrayBufferObject;
};


#endif

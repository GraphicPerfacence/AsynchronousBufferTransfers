
#ifndef __OPENGL_BATCH__
#define __OPENGL_BATCH__


#include "BatchBase.h"

class Batch : public BatchBase
{
public:
	Batch(void);
	virtual ~Batch(void);

	// Start populating the array
	void Begin(unsigned int primitive, unsigned int nVerts, unsigned int nTextureUnits = 0);

	// Tell the batch you are done
	void End(void);

	// Block Copy in vertex data
	void CopyVertexData3f(Vec3f *vVerts);
	void CopyNormalDataf(Vec3f *vNorms);
	void CopyColorData4f(Vec4f *vColors);
	void CopyTexCoordData2f(Vec2f *vTexCoords, unsigned int uiTextureLayer);

	// Just to make life easier...
	inline void CopyVertexData3f(float *vVerts) { CopyVertexData3f((Vec3f *)(vVerts)); }
	inline void CopyNormalDataf(float *vNorms) { CopyNormalDataf((Vec3f *)(vNorms)); }
	inline void CopyColorData4f(float *vColors) { CopyColorData4f((Vec4f *)(vColors)); }
	inline void CopyTexCoordData2f(float *vTex, unsigned int uiTextureLayer) { CopyTexCoordData2f((Vec2f *)(vTex), uiTextureLayer); }

	virtual void Draw(void);

	// Immediate mode emulation
	// Slowest way to build an array on purpose... Use the above if you can instead
	void Reset(void);

	void Vertex3f(float x, float y, float z);
	void Vertex3fv(Vec3f vVertex);

	void Normal3f(float x, float y, float z);
	void Normal3fv(Vec3f vNormal);

	void Color4f(float r, float g, float b, float a);
	void Color4fv(Vec4f vColor);

	void MultiTexCoord2f(unsigned int texture, float s, float t);
	void MultiTexCoord2fv(unsigned int texture, Vec2f vTexCoord);

protected:
	unsigned int 		primitiveType;		// What am I drawing....
	unsigned int		uiVertexArray;
	unsigned int		uiNormalArray;
	unsigned int		uiColorArray;
	unsigned int		*uiTextureCoordArray;
	unsigned int		vertexArrayObject;

	unsigned int		nVertsBuilding;			// Building up vertexes counter (immediate mode emulator)
	unsigned int		nNumVerts;				// Number of verticies in this batch
	unsigned int		nNumTextureUnits;		// Number of texture coordinate sets

	bool				bBatchDone;				// Batch has been built


	Vec3f *pVerts;
	Vec3f *pNormals;
	Vec4f *pColors;
	Vec2f **pTexCoords;

};

#endif // __GL_BATCH__

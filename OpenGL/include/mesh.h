//
//  mesh.h
//  OpenGL
//
//  Created by xt on 15/8/30.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__mesh__
#define __OpenGL__mesh__

#include <vector> 
#include <string>

struct VertexFormat
{
	float position_x, position_y, position_z;				 
	float normal_x, normal_y, normal_z;						 
	float texcoord_x, texcoord_y;							 
	float tangent_x,tangent_y,tangent_z;
	float bitangent_x,bitangent_y,bitangent_z;
	VertexFormat()
	{
		position_x = position_y = position_z = 0;
		normal_x = normal_y = normal_z = 0;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz)
	{
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = normal_y = normal_z = 0;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz, float nx, float ny, float nz)
	{
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = nx;		normal_y = ny;		normal_z = nz;
		texcoord_x = texcoord_y = 0;
	}
	VertexFormat(float px, float py, float pz, float tx, float ty)
	{
		position_x = px;		position_y = py;		position_z = pz;
		texcoord_x = tx;		texcoord_y = ty;
		normal_x = normal_y = normal_z = 0;
	}
	VertexFormat(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty)
	{
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = nx;		normal_y = ny;		normal_z = nz;
		texcoord_x = tx;		texcoord_y = ty;
	}
	VertexFormat(float px, float py, float pz, float nx, float ny, float nz, float tx, float ty,
		float ttx,float tty,float ttz,float bx,float by,float bz)
	{
		position_x = px;		position_y = py;		position_z = pz;
		normal_x = nx;		normal_y = ny;		normal_z = nz;
		texcoord_x = tx;		texcoord_y = ty;
		tangent_x = ttx;		tangent_y = tty;tangent_z = ttz;
		bitangent_x = bx;bitangent_y = by;bitangent_z = bz;
	}

	VertexFormat operator=(const VertexFormat &rhs)
	{
		position_x = rhs.position_x;	position_y = rhs.position_y;	position_z = rhs.position_z;
		normal_x = rhs.normal_x;		normal_y = rhs.normal_y;		normal_z = rhs.normal_z;
		texcoord_x = rhs.texcoord_x;	texcoord_y = rhs.texcoord_y;
		tangent_x = rhs.tangent_x; tangent_y = rhs.tangent_y; tangent_z = rhs.tangent_z;
		bitangent_x = rhs.bitangent_x;bitangent_y = rhs.bitangent_y;bitangent_z = rhs.bitangent_z;
		return (*this);
	}
};

//for assimp file
struct TextureR
{
	unsigned int id;
	std::string type;
	std::string texturePath;

};

class Shader;


class Mesh
{
public:

	Mesh();

	~Mesh();

	void destory(void);
	
	void setupMesh(void);

	void setupMesh(std::vector<VertexFormat>&,std::vector<unsigned int >&ic,std::vector<TextureR>&ts);
	
	void draw(const Shader*shader)const;

private:
	unsigned int                    _VAOID;

	unsigned int                    _VBOID;
	unsigned int                    _IBOID; //indices index

	unsigned int					_indicesCount;

	std::vector<TextureR> _textures;
	std::vector<VertexFormat> _vertexs;
	std::vector<unsigned int > _elementIndices;

};

class INode
{
	public:

	enum AssimpPostProcessSteps
	{
		aiProcess_No = 0x00, //不使用Assimpost

		aiProcess_CalcTangentSpace = 0x1,
		aiProcess_JoinIdenticalVertices = 0x2,
		aiProcess_MakeLeftHanded = 0x4,
		aiProcess_Triangulate = 0x8,
		aiProcess_RemoveComponent = 0x10,
		aiProcess_GenNormals = 0x20,
		aiProcess_GenSmoothNormals = 0x40,
		aiProcess_SplitLargeMeshes = 0x80,
		aiProcess_PreTransformVertices = 0x100,
		aiProcess_LimitBoneWeights = 0x200,
		aiProcess_ValidateDataStructure = 0x400,
		aiProcess_ImproveCacheLocality = 0x800,
		aiProcess_RemoveRedundantMaterials = 0x1000,
		aiProcess_FixInfacingNormals = 0x2000,
		aiProcess_SortByPType = 0x8000,
		aiProcess_FindDegenerates = 0x10000,
		aiProcess_FindInvalidData = 0x20000,
		aiProcess_GenUVCoords = 0x40000,
		aiProcess_TransformUVCoords = 0x80000,
		aiProcess_FindInstances = 0x100000,
		aiProcess_OptimizeMeshes  = 0x200000, 
		aiProcess_OptimizeGraph  = 0x400000, 
		aiProcess_FlipUVs = 0x800000, 
		aiProcess_FlipWindingOrder  = 0x1000000,
		aiProcess_SplitByBoneCount  = 0x2000000,
		aiProcess_Debone  = 0x4000000
	};

	INode(const char*fileName,unsigned int step);
	
	bool initMesh(const char* fileName ,unsigned int steps);

	void drawNode(const Shader*shader);

	private:
	std::vector<Mesh> _meshs;
};
#endif
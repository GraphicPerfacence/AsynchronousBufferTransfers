
#include "../include/XReadFile.h"
#include "../include/comm.h"
#include "../include/log.h"
#include "SOIL2/SOIL2.h"
#include <iostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <gl/glew.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>



bool loadOBJ(const char * path,
	std::vector < glm::vec3 > & out_vertices,
	std::vector < glm::vec2 > & out_uvs,
	std::vector < glm::vec3 > & out_normals)
{
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file = fopen(path, "r");
	if (file == NULL)
	{
		printf("Impossilbe to open the file\n");
		return false;
	}


	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0)
		{

			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		else
		{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}


	}
	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		glm::vec3 normal = temp_normals[normalIndex - 1];

		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		out_uvs.push_back(uv);
		out_normals.push_back(normal);

	}
	return true;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

unsigned int loadDDS(const char * imagepath)
{

	unsigned char header[124];

	FILE *fp;

	/* try to open the file */
	fp = fopen(imagepath, "rb");
	if (fp == NULL) {
		printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", imagepath); getchar();
		return 0;
	}

	/* verify the type of file */
	char filecode[4];
	fread(filecode, 1, 4, fp);
	if (strncmp(filecode, "DDS ", 4) != 0) {
		fclose(fp);
		return 0;
	}

	/* get the surface desc */
	fread(&header, 124, 1, fp);

	unsigned int height = *(unsigned int*)&(header[8]);
	unsigned int width = *(unsigned int*)&(header[12]);
	unsigned int linearSize = *(unsigned int*)&(header[16]);
	unsigned int mipMapCount = *(unsigned int*)&(header[24]);
	unsigned int fourCC = *(unsigned int*)&(header[80]);


	unsigned char * buffer;
	unsigned int bufsize;
	/* how big is it going to be including all mipmaps? */
	bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
	buffer = (unsigned char*)malloc(bufsize * sizeof(unsigned char));
	fread(buffer, 1, bufsize, fp);
	/* close the file pointer */
	fclose(fp);

	unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
	unsigned int format;
	switch (fourCC)
	{
	case FOURCC_DXT1:
		format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
		break;
	case FOURCC_DXT3:
		format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
		break;
	case FOURCC_DXT5:
		format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
		break;
	default:
		free(buffer);
		return 0;
	}

	// Create one OpenGL texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
	unsigned int offset = 0;

	/* load the mipmaps */
	for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
	{
		unsigned int size = ((width + 3) / 4)*((height + 3) / 4)*blockSize;
		glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
			0, size, buffer + offset);

		offset += size;
		width /= 2;
		height /= 2;

		// Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
		if (width < 1) width = 1;
		if (height < 1) height = 1;

	}

	free(buffer);

	return textureID;


}

unsigned int soil_load_DDS(const char* imagePath)
{
	GLuint tex_2d = SOIL_direct_load_DDS(imagePath, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_TEXTURE_REPEATS, 0);

	if (0 == tex_2d)
	{
		printf("SOIL loading DDS error: '%s' \n", SOIL_last_result());
	}

	return tex_2d;
}

unsigned int loadBMP_custom(const char*imagePath)
{
	struct bmpHeader
	{
		unsigned char type[2];
		int f_lenght;
		short rezerved1;
		short rezerved2;
		int offBits;
	};
	struct header_info
	{
		int size;
		int width;
		int height;
		short planes;
		short bitCount;
		int compresion;
		int sizeImage;
		int xPelsPerMeter;
		int yPelsPerMeter;
		int clrUsed;
		int clrImportant;
	};

	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;       // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;     // = width*height*3
	unsigned char* data;

	FILE * file = fopen(imagePath, "rb");
	if (!file)
	{
		printf("Image could not be opened\n"); return 0;
	}
	if (fread(header, 1, 54, file) != 54)
	{
		printf("Not a correct BMP file\n");
		return false;
	}

	if (header[0] != 'B' || header[1] != 'M') {
		printf("Not a correct BMP file\n");
		return 0;
	}

	// Read ints from the byte array
	dataPos = *(int*)&(header[0x0A]);
	imageSize = *(int*)&(header[0x22]);
	width = *(int*)&(header[0x12]);
	height = *(int*)&(header[0x16]);

	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

	data = new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	//create opengl texture
	GLuint textureID;
	glGenTextures(1, &textureID);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;
}

unsigned int TextureFromFile(const char* path, const char* directory, bool gamma = false)
{
	//Generate texture ID and load texture data 
	char buffer[128];
	sprintf(buffer, "%s/%s",directory,path);

	//string filename = string(path);
	//filename = directory + '/' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);
	int width,height;
	unsigned char* image = SOIL_load_image(buffer, &width, &height, 0, SOIL_LOAD_RGB);
	// Assign texture to ID
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, gamma ? GL_SRGB : GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);	

	// Parameters
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);

	return textureID;
}


std::vector<TextureR> loadMaterialTextures(const char*fileName, aiMaterial* mat, aiTextureType type, const char* typeName)
{
	std::vector<TextureR> textures;

	for(GLuint i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);

		GLboolean skip = false;
		for(GLuint j = 0; j < already_loadedTextures.size(); j++)
		{
			if(aiString(already_loadedTextures[j].texturePath) == str)
			{
				textures.push_back(already_loadedTextures[j]);
				skip = true; // A texture with the same filepath has already been loaded, continue to next one. (optimization)
				break;
			}
		}
		if(!skip)
		{   // If texture hasn't been loaded already, load it
			TextureR texture;
			std::string path = fileName;
			path = path.substr(0,path.find_last_of('/'));
			texture.id = TextureFromFile(str.C_Str(), path.c_str());
			texture.type = typeName;
			texture.texturePath = str.C_Str();
			textures.push_back(texture);
			already_loadedTextures.push_back(texture);  // Store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
		}
	}
	return textures;
}

void processMesh(const char*fileName,const aiMesh* mesh, const aiScene* scene,Mesh&meshs)
{
	std::vector<VertexFormat> vertexs;
	std::vector<unsigned int >indices;
	// Walk through each of the mesh's vertices
	for(GLuint i = 0; i < mesh->mNumVertices; i++)
	{

		Vec3f Position; // We declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		Vec3f normal;
		Vec2f tex;
		Vec3f tb;

		// Positions
		Position.x = mesh->mVertices[i].x;
		Position.y = mesh->mVertices[i].y;
		Position.z = mesh->mVertices[i].z;

		// Normals
		normal.x = mesh->mNormals[i].x;
		normal.y = mesh->mNormals[i].y;
		normal.z = mesh->mNormals[i].z;

		// Texture Coordinates
		if(mesh->mTextureCoords[0]) // Does the mesh contain texture coordinates?
		{
			// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			tex.x = mesh->mTextureCoords[0][i].x;
			tex.y = mesh->mTextureCoords[0][i].y;
		}
		else
			tex = glm::vec2(0.0f, 0.0f);
		// Tangent
		Vec3f tangent;
		tangent.x = mesh->mTangents[i].x;
		tangent.y = mesh->mTangents[i].y;
		tangent.z = mesh->mTangents[i].z;

		Vec3f bitangent;
		bitangent.x = mesh->mBitangents[i].x;
		bitangent.y = mesh->mBitangents[i].y;
		bitangent.z = mesh->mBitangents[i].z;

		vertexs.push_back(
			VertexFormat(
			Position.x,Position.y,Position.z,
			normal.x,normal.y,normal.z,
			tex.x,tex.y,
			tangent.x,tangent.y,tangent.z,
			bitangent.x,bitangent.y,bitangent.z));
	}

	for(GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// Retrieve all indices of the face and store them in the indices vector
		for(GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	std::vector<TextureR> texs;

	if(mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		std::vector<TextureR> diffuseMaps = loadMaterialTextures(fileName, material, aiTextureType_DIFFUSE, "texture_diffuse");
		texs.insert(texs.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. Specular maps
		std::vector<TextureR> specularMaps = loadMaterialTextures(fileName,material, aiTextureType_SPECULAR, "texture_specular");
		texs.insert(texs.end(), specularMaps.begin(), specularMaps.end());
		// 3. Normal maps
		std::vector<TextureR> normalMaps = loadMaterialTextures(fileName,material, aiTextureType_HEIGHT, "texture_normal");
		texs.insert(texs.end(), normalMaps.begin(), normalMaps.end());
		// 4. Height maps
		std::vector<TextureR> heightMaps = loadMaterialTextures(fileName,material, aiTextureType_AMBIENT, "texture_height");
		texs.insert(texs.end(), heightMaps.begin(), heightMaps.end());
	}
	
	//meshs.push_back(Mesh());
	meshs.setupMesh(vertexs,indices,texs);
}

void processNode(const char*fileName,const aiNode* node, const aiScene* scene,std::vector<Mesh>&meshs)
{
	// Process each mesh located at the current node
	for(GLuint i = 0; i < node->mNumMeshes; i++)
	{
		// The node object only contains indices to index the actual objects in the scene. 
		// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		const aiMesh* mesh = scene->mMeshes[node->mMeshes[i]]; 
		//meshs.push_back(processMesh(fileName, mesh, scene));
		aiMesh& newMesh = meshs[meshIndices];
		meshIndices++;

		processMesh(fileName, mesh, scene,newMesh);			
	}
	// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for(GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(fileName, node->mChildren[i], scene,meshs);
	}
}

bool loadObjByAssimp(const char*fileName,std::vector<Mesh>&meshs,unsigned int steps)
{

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(fileName,steps);
	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		char buffer[128];
		sprintf(buffer,"ERROR::ASSIMP:: %s \n",importer.GetErrorString());
		Log::Instance()->printMessage(buffer);
		return false;
	}

	meshs = std::vector<Mesh> (scene->mNumMeshes,Mesh());
	meshIndices = 0;
	processNode(fileName,scene->mRootNode,scene,meshs);

	return true;
}



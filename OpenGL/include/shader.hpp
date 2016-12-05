#ifndef __OpenGL__shader__
#define __OpenGL__shader__


#include <vector>

typedef void(*funB) (unsigned int);
typedef void(*funA)();

class Shader
{
public:

	// Create an empty constructor and have the deconstructor release our memory.
	Shader() { }
	
	~Shader() { Destroy(); }

	unsigned int  LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char*geometry_file_path = NULL);

	unsigned int  LoadShaderSouce(const char* vertexSource, const char* fragmentSource, const char* geometrySource);
	
	unsigned int LoadShadersAlex(const char * vertex_file_path, const char * fragment_file_path);
	// This loads a vertex and fragment shader from a text file (relative or full path)
	void Initialize(const char* strVertexFile, const char* strFragmentFile);

	// This returns an ID for a variable in our shader, to be used with a Set*() function
	int GetVariable(const char* strVariable)const;

	unsigned int GetUniformBlockIndex(const char* uniformVariable);

	// Below are functions to set an integer, a set of floats or a matrix (float[16])
	void SetInt(int id, int newValue)const;
	void SetFloat(int id, float newValue)const;
	void SetFloat2(int id, float v0, float v1);
	void SetFloat3(int id, float v0, float v1, float v2);
	void SetFloat4(int id, float v0, float v1, float v2, float v3);
	void SetUniformBlocking(int id, unsigned int value);

	void SetFloat3V(int id, unsigned int count, const float*values);
	// This allows us to pass in 4x4 matrix (float array of 16) to a shader by the Id received from GetVariable()
	void SetMatrix4(int id, unsigned int count, bool transpose, const float *value);

	// These 2 functions turn on and off our shader, which uses the OpenGL glUseProgram() function
	void TurnOn();
	void TurnOff();

	// This releases our memory for our shader
	void Destroy();

	unsigned int getShaderId()const { return ShaderProgramId; }

private:
	void GLBindAttribLocation();
	void getUniformLocation();
	void setUniformVal();

private:

	unsigned int      VertexShaderId;
	unsigned int      FragmentShaderId;
	unsigned int      GeometryShaderId;
	unsigned int      ShaderProgramId;
};


#endif


#include "../include/log.h"
#include "../include/shader.hpp"

#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

#include <gl/glew.h>


GLuint Shader::LoadShaders(const char * vertex_file_path, const char * fragment_file_path, const char*geometry_file_path) {


	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);

	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();

	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", fragment_file_path);
		getchar();
		return 0;
	}
	//Read geometry_file_path
	std::string GeometryShaderCode;
	if (geometry_file_path != NULL)
	{
		std::ifstream GeometryShaderStream(geometry_file_path, std::ios::in);
		if (GeometryShaderStream.is_open())
		{
			std::string Line = "";
			while (getline(GeometryShaderStream, Line))
				GeometryShaderCode += "\n" + Line;
			GeometryShaderStream.close();
		}
		else
		{
			printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", geometry_file_path);
			getchar();
			return 0;
		}

	}
	return LoadShaderSouce(VertexShaderCode.c_str(), FragmentShaderCode.c_str(), GeometryShaderCode.c_str());

}

GLuint Shader::LoadShaderSouce(const char* vertexSource, const char*fragmentSource, const char* geometrySource)
{

	// Create the shaders
	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	if (!geometrySource) GeometryShaderId = glCreateShader(GL_GEOMETRY_SHADER);

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling vertex shader ...");


	char const * VertexSourcePointer = vertexSource;
	glShaderSource(VertexShaderId, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderId);

	// Check Vertex Shader
	Log::Instance()->printOglError(__FILE__, __LINE__);
	glGetShaderiv(VertexShaderId, GL_COMPILE_STATUS, &Result);
	Log::Instance()->printShaderInfoLog(VertexShaderId);
	if (!GL_TRUE) return 0;


	// Compile Fragment Shader
	printf("Compiling frame shader ...\n");
	char const * FragmentSourcePointer = fragmentSource;
	glShaderSource(FragmentShaderId, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderId);

	// Check Fragment Shader
	Log::Instance()->printOglError(__FILE__, __LINE__);
	glGetShaderiv(FragmentShaderId, GL_COMPILE_STATUS, &Result);
	Log::Instance()->printShaderInfoLog(FragmentShaderId);
	if (!GL_TRUE) return 0;

	//COMPILE GEOMETRY SAHDER
	if (!geometrySource)
	{
		char const * GeometrySourcePointer = geometrySource;
		glShaderSource(GeometryShaderId, 1, &GeometrySourcePointer, NULL);
		glCompileShader(GeometryShaderId);

		// Check Fragment Shader
		Log::Instance()->printOglError(__FILE__, __LINE__);
		glGetShaderiv(GeometryShaderId, GL_COMPILE_STATUS, &Result);
		Log::Instance()->printShaderInfoLog(GeometryShaderId);
		if (!GL_TRUE) return 0;
	}

	// Link the program
	printf("Linking program...\n");
	ShaderProgramId = glCreateProgram();
	glAttachShader(ShaderProgramId, VertexShaderId);
	glAttachShader(ShaderProgramId, FragmentShaderId);
	if (!geometrySource) glAttachShader(ShaderProgramId, GeometryShaderId);
	GLBindAttribLocation();


	glLinkProgram(ShaderProgramId);

	// Check the program
	glGetProgramiv(ShaderProgramId, GL_LINK_STATUS, &Result);
	glGetProgramiv(ShaderProgramId, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ShaderProgramId, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}
	if (!GL_TRUE) return 0;

	return ShaderProgramId;
}

// This function loads a vertex and fragment shader file and creates them
void Shader::Initialize(const char* strVertexFile, const char* strFragmentFile)
{
	LoadShaders(strVertexFile, strFragmentFile);
}

// This function returns a variable Id for a shader variable.  This is used
// when we need to pass in variables into a shader like numbers and matrices.
int Shader::GetVariable(const char* strVariable)const
{
	// If we don't have an active program object, let's return -1
	if (!ShaderProgramId)
		return -1;

	// This returns the variable Id for a variable in a shader file
	GLint loc = glGetUniformLocation(ShaderProgramId, strVariable);
	if (loc == -1)
	{
		 printf("%s dose not exist \n", strVariable);
	}
	return loc;
}

unsigned int Shader::GetUniformBlockIndex(const char* uniformVariable)
{
	if (!ShaderProgramId)
		return -1;
	GLuint loc = -1;

	loc = glGetUniformBlockIndex(ShaderProgramId, uniformVariable);

	return loc;
}

void Shader::SetInt(int id, int newValue)const
{
	glUniform1i(id, newValue);
}

void Shader::SetFloat(int id, float newValue)const
{
	glUniform1f(id, newValue);
}

void Shader::SetFloat2(int id, float v0, float v1)
{
	glUniform2f(id, v0, v1);
}

void Shader::SetFloat3(int id, float v0, float v1, float v2)
{
	glUniform3f(id, v0, v1, v2);
}

void Shader::SetFloat4(int id, float v0, float v1, float v2, float v3)
{
	glUniform4f(id, v0, v1, v2, v3);
}

// This function frees all of our shader data
void Shader::Destroy()
{
	// If our vertex shader pointer is valid, free it
	if (VertexShaderId)
	{
		glDetachShader(ShaderProgramId, VertexShaderId);
		glDeleteShader(VertexShaderId);
		VertexShaderId = 0;
	}

	// If our fragment shader pointer is valid, free it
	if (FragmentShaderId)
	{
		glDetachShader(ShaderProgramId, FragmentShaderId);
		glDeleteShader(FragmentShaderId);
		FragmentShaderId = 0;
	}

	// If our program object pointer is valid, free it
	if (ShaderProgramId)
	{
		glDeleteShader(ShaderProgramId);
		ShaderProgramId = 0;
	}
}

void Shader::SetUniformBlocking(GLint id, GLuint value)
{
	glUniformBlockBinding(ShaderProgramId, id, value);
}


void Shader::SetFloat3V(int id, unsigned int count, const float*values)
{
	glUniform3fv(id, count, values);
}

void Shader::SetMatrix4(int id, unsigned int count, bool transpose, const float *value)
{
	glUniformMatrix4fv(id, count, transpose, value);
}

void Shader::TurnOn()
{
	glUseProgram(ShaderProgramId);
}

void Shader::TurnOff()
{
	glUseProgram(0);
}

void Shader::GLBindAttribLocation()
{
	//    glBindAttribLocation(ShaderProgramId,0,"vertexPosition_modelspace");
	//    glBindAttribLocation(ShaderProgramId,1,"vertexColor");
	//    glBindAttribLocation(ShaderProgramId,2,"vertexUV");
}

void Shader::getUniformLocation()
{

}

void Shader::setUniformVal()
{

}

unsigned int Shader::LoadShadersAlex(const char * vertex_file_path, const char * fragment_file_path)
{
	// Create the shaders
	GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	// Read the Vertex Shader code from the file
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
	if (VertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else 
	{
		printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
		getchar();
		return 0;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
	if (FragmentShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}

	GLint Result = GL_FALSE;
	int InfoLogLength;

	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertex_file_path);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
	glCompileShader(VertexShaderID);

	// Check Vertex Shader
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0)
	{
		std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
		printf("%s\n", &VertexShaderErrorMessage[0]);
	}



	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragment_file_path);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
	glCompileShader(FragmentShaderID);

	// Check Fragment Shader
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
		printf("%s\n", &FragmentShaderErrorMessage[0]);
	}

	// Link the program
	printf("Linking program\n");
	GLuint ProgramID = glCreateProgram();
	ShaderProgramId = ProgramID;
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);

	// Check the program
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if (InfoLogLength > 0) 
	{
		std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
		printf("%s\n", &ProgramErrorMessage[0]);
	}

	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);

	return ProgramID;
}

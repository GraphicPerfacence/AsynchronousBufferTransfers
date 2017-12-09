//
//  Model.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "Scene.h"
#include "GLFWManager.h"
#include "shader.hpp"
#include "TimerManager.h"
#include "glfwSet.h"
#include "sys.h"
#include "log.h"
#include "camera.h"
#include "geometry.h"
#include "texture.h"
#include "XTimer.h"
#include "fileSytem.h"
#include "util/Subdivision.hpp"
#include  <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>

const unsigned int NR_LIGHTS = 32;
///////////////////// Just For This Test//////////////////////////////

 

///////////////////////////////////////////////////////////////////

GLuint cubInt;
GLuint floorInt;
GLuint earth_vertex_buffer;
GLuint indicesNum;
std::string textureFilePath = "/Users/glp/Documents/osgResource/OpenSceneGraph-Data-3.0.0/Images/forestRoof.png";

TextureObj * tmp;

glm::vec4 normalize_plane(const glm::vec4 &p) {
	//return p*(1.0f/length(p.swizzle(glm::comp::X,glm::comp::Y,glm::comp::Z)));
    return glm::vec4();
}


Scene::Scene()
{
}

void Scene::Initialize()
{
    initOpengl();
    initTexture();
    initSceneObjs();
    initShader();
}

void Scene::initOpengl(void)
{
	glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void Scene::initTexture(void)
{
    TextureObj * curTexObj = new TextureObj(textureFilePath.c_str());
    curTexObj->InterFormat(GL_RGB);
    curTexObj->ExternFormat(GL_RGB);
    curTexObj->DataType(GL_UNSIGNED_BYTE);
    curTexObj->Bind();
    curTexObj->Data();
    curTexObj->FilterLinear();
    curTexObj->MirrorRepeat();
    curTexObj->UnBind();
    
    _texturesObj.push_back(curTexObj);

}

void Scene::initBOs(GLuint size)
{


}

void Scene::initFBO(void)
{
}

void Scene::initLight(void)
{
	 
}

void Scene::initShader(void)
{
    std::string  shaderBasePath;
    shaderBasePath = "/Users/glp/Documents/projects/OpenGL/OpenGL/shader/";

    _shaders.push_back(new Shader); //

    std::string vs = shaderBasePath + "basic.vs";
    std::string fs = shaderBasePath + "basic.frag";
    _shaders[0]->LoadShaders(vs.c_str(), fs.c_str(), nullptr);

}

void Scene::initSceneObjs(void)
{

    std::vector<V3f> positions;
    std::vector<unsigned int > indices;
    std::vector<V3f> normals;
    Util::Subdivision::subdivisionSphere(positions,indices,5);

    if((positions.size() < 0) || (indices.size() < 0)) return;

    indicesNum = indices.size();

    GLuint VBO;
    GLuint IVBO;
    glGenVertexArrays(1,&earth_vertex_buffer); //vao
    glGenBuffers(1,&VBO);
    glGenBuffers(1,&IVBO);

    glBindVertexArray(earth_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * positions.size(), &positions[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
                          0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                          3,                  // size
                          GL_FLOAT,           // type
                          GL_FALSE,           // normalized?
                          0,                  // stride
                          (void*)0            // array buffer offset
                          );
    
    glBindVertexArray(0);
}

void Scene::Render()
 {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Shader * currentShader = _shaders[0];
    currentShader->TurnOn();

    initUniformVal(currentShader);
    
    glBindVertexArray(earth_vertex_buffer);

    //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDrawElements(GL_TRIANGLES, indicesNum, GL_UNSIGNED_INT, (void*)0);

    glBindVertexArray(0);

}

// This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
void Scene::Destroy()
{
}

void Scene::initThisDemo(void)
{
}

void Scene::setScreenWH(unsigned int w,unsigned int h)
{
	_screenWidth = w;
	_screenHeight = h;
}

void Scene::createSceneData(void)
{

}


void modelInput(InputCodes code)
{
	switch (code)
	{
	case  InputCodes::b:
		 
		break;
	case  InputCodes::c:
		 
		break;
	case InputCodes::u:
		break;
	case InputCodes::y:
		break;
	default:
		break;
	}
}

void windowSize(GLFWwindow*window, int width, int height)  
{
	glViewport(0, 0, width, height);
}

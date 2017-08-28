//
//  Model.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#include "../include/Scene.h"
#include "../include/GLFWManager.h"
#include "../include/shader.hpp"
#include "../include/TimerManager.h"
#include "../include/glfwSet.h"
#include "../include/sys.h"
#include "../include/log.h"
#include "../include/camera.h"
#include "../include/geometry.h"
#include "../include/texture.h"
#include "../include/XTimer.h"
#include "../include/fileSytem.h"

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
GLuint billboard_vertex_buffer;
std::string textureFilePath = "/Users/glp/Documents/modelsAndImgs/textures/cursor_crosshair_inverse.png";

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
    _shaders.push_back(new Shader); //

        //shaderGeometryPass
    std::string vs = shaderBasePath + "Billboard.vert";
    std::string fs = shaderBasePath + "Billboard.frag";
    _shaders[0]->LoadShaders(vs.c_str(), fs.c_str(), nullptr);


    vs = shaderBasePath + "basic.vs";
    fs = shaderBasePath + "basic.frag";
    _shaders[1]->LoadShaders(vs.c_str(), fs.c_str(), nullptr);


    //perp
    _shaders[0]->TurnOn();
    GLint location =  _shaders[0]->GetVariable("myTextureSampler");
    _shaders[0]->SetInt(location,0);
    _shaders[0]->TurnOff();

//
//        //shaderSSAOBlur
//    vs = shaderBasePath + "ssao.vert";
//    fs = shaderBasePath + "ssao_blur.frag";
//    shaders[2]->LoadShaders(vs.c_str(), fs.c_str(), nullptr);
//    shaders[2]->TurnOn();
//    location = shaders[2]->GetVariable("ssaoInput");
//    shaders[2]->SetInt(location,0);
//    shaders[2]->TurnOff();
//
//        //shaderLightingPass
//    vs = shaderBasePath + "ssao.vert";
//    fs = shaderBasePath + "ssao_lighting.frag";
//    shaders[3]->LoadShaders(vs.c_str(), fs.c_str(), nullptr);

}

void Scene::initSceneObjs(void)
{

    initCub(cubInt);

    static const GLfloat g_vertex_buffer_data[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
        0.5f,  0.5f, 0.0f,
    };

    GLuint VBO;
    glGenVertexArrays(1,&billboard_vertex_buffer);
    glGenBuffers(1,&VBO);

    glBindVertexArray(billboard_vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_DYNAMIC_DRAW);
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint location =  currentShader->GetVariable("myTextureSampler");

    glActiveTexture(GL_TEXTURE0);
    currentShader->SetInt(location,0);
     _texturesObj[0]->Bind();

    Camera * camera = GetCamera();
    glm::mat4 viewMatrix =  camera->GetViewMatrix();
    glm::mat4 projectMatrix = camera->GetProjectionMatrix();
    glm::mat4 viewProjectionMatrix = projectMatrix * viewMatrix;


    GLuint CameraRight_worldspace_ID  = currentShader->GetVariable("CameraRight_worldspace");
	GLuint CameraUp_worldspace_ID  = currentShader->GetVariable( "CameraUp_worldspace");
	GLuint ViewProjMatrixID = currentShader->GetVariable("VP");
	GLuint BillboardPosID = currentShader->GetVariable("BillboardPos");
	GLuint BillboardSizeID = currentShader->GetVariable( "BillboardSize");
	GLuint LifeLevelID = currentShader->GetVariable( "LifeLevel");

 currentShader->SetFloat3(CameraRight_worldspace_ID,viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
 currentShader->SetFloat3(CameraUp_worldspace_ID,viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);

 currentShader->SetFloat3(BillboardPosID,0.0f, 0.5f, -10.0f);
 currentShader->SetFloat2(BillboardSizeID,1.0f, 0.125f);

 double curTime = glfwGetTime();
 float LifeLevel = sin(curTime)*0.1f + 0.7f;
 currentShader->SetFloat(LifeLevelID, LifeLevel);

 currentShader->SetMatrix4(ViewProjMatrixID, 1, GL_FALSE,glm::value_ptr(viewProjectionMatrix));

 glBindVertexArray(billboard_vertex_buffer);

 glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

 glBindVertexArray(0);

 currentShader->TurnOff();

 currentShader = _shaders[1];
 currentShader->TurnOn();
 initUniformVal(currentShader);
 drawCub(cubInt);
 currentShader->TurnOff();


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

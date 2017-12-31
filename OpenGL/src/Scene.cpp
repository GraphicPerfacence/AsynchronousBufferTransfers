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
#include "ElliposidGeometry.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>

const unsigned int NR_LIGHTS = 32;

Util::ElliposidGeometry eg;

std::string textureFilePath = "/Users/glp/Documents/osgResource/OpenSceneGraph-Data-3.0.0/Images/earth.jpg";

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

    int eunit = _shaders[0]->GetVariable("earthSample");
    glUniform1i(eunit,0);
}

void Scene::initSceneObjs(void)
{
    eg._subType = Util::Subdivision::GEOGRAPHICGRID;
    eg.create();
}

void Scene::Render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Shader * currentShader = _shaders[0];
    currentShader->TurnOn();

    initUniformVal(currentShader);

    eg.DrawElliposid();

}

    // This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
void Scene::Destroy()
{
}

void Scene::initThisDemo(void)
{
}


void Scene::createSceneData(void)
{

}


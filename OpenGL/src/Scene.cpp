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
#include "Ellipsoid.h"

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

    std::vector<V3f> positions;
    std::vector<unsigned int > indices;
    std::vector<V3f> normals;
    std::vector<V2f> texCoords;
    Ellipsoid<float> ellipsoid(1.0,1.1,1.0);

    Util::Subdivision::TYPE type = Util::Subdivision::GEOGRAPHICGRID;

    Util::Subdivision::subdivisionElliposid(&ellipsoid,type, &positions,indices,&normals,&texCoords,5);

    if((positions.size() < 0) || (indices.size() < 0)) return;

    indicesNum = indices.size();

    if(Util::Subdivision::TETRAHEDRON)
        {
        GLuint VBO[3];
        glGenVertexArrays(1,&earth_vertex_buffer); //vao
        glGenBuffers(3,VBO);


        glBindVertexArray(earth_vertex_buffer);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * positions.size(), &positions[0], GL_STATIC_DRAW);


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]);
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

        glBindBuffer(GL_ARRAY_BUFFER,VBO[1]);
        glBufferData(GL_ARRAY_BUFFER,sizeof(V2f) * texCoords.size(),&texCoords[0],GL_STATIC_DRAW);


        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                              1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        glBindVertexArray(0);

        }
    else if ( Util::Subdivision::GEOGRAPHICGRID == type)
        {
        short slip = Util::Subdivision::numberOfSlicePartitions;
        short stack = Util::Subdivision::numberOfStackPartitions;


        glGenVertexArrays(1,&earth_vertex_buffer); //vao
        GLuint VBO[3];
        glGenBuffers(3,VBO);


        glBindVertexArray(earth_vertex_buffer);

        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(V3f) * positions.size(), &positions[0], GL_STATIC_DRAW); //position

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, VBO[2]); //top fan
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

        glBindBuffer(GL_ARRAY_BUFFER,VBO[1]); //texCoord
        glBufferData(GL_ARRAY_BUFFER,sizeof(V2f) * texCoords.size(),&texCoords[0],GL_STATIC_DRAW);


        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
                              1,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        glBindVertexArray(0);


        }
}

void Scene::Render()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    Shader * currentShader = _shaders[0];
    currentShader->TurnOn();

    initUniformVal(currentShader);

    glBindVertexArray(earth_vertex_buffer);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _texturesObj[0]->GetTexture());
        //glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glDrawElements(GL_TRIANGLE_FAN, Util::Subdivision::numberOfSlicePartitions * 3 , GL_UNSIGNED_INT, (void*)0);
    glDrawElements(GL_TRIANGLE_STRIP, indicesNum - 6 * Util::Subdivision::numberOfSlicePartitions , GL_UNSIGNED_INT, (void*)(Util::Subdivision::numberOfSlicePartitions * 3));
    glDrawElements(GL_TRIANGLE_FAN, Util::Subdivision::numberOfSlicePartitions * 3, GL_UNSIGNED_INT, (void*)(indicesNum -  Util::Subdivision::numberOfSlicePartitions * 3));

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

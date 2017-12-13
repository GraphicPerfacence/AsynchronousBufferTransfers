//
//  BaseRender.cpp
//  
//
//  Created by xt on 16/1/31.
//
//

#include "BaseRender.h"
#include "shader.hpp"
#include "camera.h"

#include <gl/glew.h>
#include <glm/gtc/type_ptr.hpp>

BaseRender::BaseRender()
{
	_uboBlock = 0;
}

void BaseRender::initUniformVal(Shader*shader ,bool modelNeed /* = true*/)
{
	GLint location = shader->GetVariable("projection");
	if(location != -1)
		shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(_camera->getProjectionMatrix()));
	location = shader->GetVariable("view");
	if(location != -1)
		shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(_camera->getViewMatrix()));

   if(modelNeed)
   {
    location = shader->GetVariable("model");
    if(location != -1)
       {
        glm::mat4 model ;
           //model = glm::rotate(model,45.0f,glm::vec3(0.0f,1.0f,0.0f));
        shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(model));
       }
   }

 //
 //   location = shader->GetVariable("lightPos");
 //   if(location != -1 && !_lights.empty())
 //       shader->SetFloat3(location,_lights[0].getPosition().x,_lights[0].getPosition().y,_lights[0].getPosition().z);
 //   
 //   location = shader->GetVariable("viewPos");
 //   if(location != -1)
 //       shader->SetFloat3(location,camera->GetPosition().x,camera->GetPosition().y,camera->GetPosition().z);
}

CameraEx<float> * BaseRender::GetCamera()const

{ return _camera; }

void  BaseRender::SetCamera(CameraEx<float> *pCamera)
{
    _camera = pCamera;
}

void BaseRender::preRenderShaderData()
{
	glm::mat4 projectionMatrix = _camera->getProjectionMatrix();

	glm::mat4 viewMatrix = _camera->getViewMatrix();

	glBindBuffer(GL_UNIFORM_BUFFER, _uboBlock);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &viewMatrix[0][0]);
	//glBindBuffer(GL_UNIFORM_BUFFER,0);
}

BaseRender::~BaseRender()
{
    for (int i = _shaders.size() - 1; i >= 0; i--)
    {
        Shader * s = _shaders[i];
        delete s;
        s = NULL;
    }

    for(int i = _texturesObj.size() - 1; i >= 0;i--)
    {
        TextureObj * to = _texturesObj[i];
        delete to;
        to = NULL;
    }
}

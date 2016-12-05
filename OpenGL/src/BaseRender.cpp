//
//  BaseRender.cpp
//  
//
//  Created by xt on 16/1/31.
//
//

#include "../include/BaseRender.h"
#include "../include/shader.hpp"
#include "../include/camera.h"

#include <gl/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

BaseRender::BaseRender()
{
	uboBlock = 0;
}

void BaseRender::initUniformVal(Shader*shader)
{
	GLint location = shader->GetVariable("projection");
	if(location != -1)
		shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(camera->GetProjectionMatrix()));
	location = shader->GetVariable("view");
	if(location != -1)
		shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(camera->GetViewMatrix()));
   
	//location = shader->GetVariable("model");
	//if(location != -1)
	//{
	//	glm::mat4 model ;
	//	//model = glm::rotate(model,45.0f,glm::vec3(0.0f,1.0f,0.0f));
	//	shader->SetMatrix4(location,1,GL_FALSE,glm::value_ptr(model));
	//}
 //  
 //   location = shader->GetVariable("lightPos");
 //   if(location != -1 && !_lights.empty())
 //       shader->SetFloat3(location,_lights[0].getPosition().x,_lights[0].getPosition().y,_lights[0].getPosition().z);
 //   
 //   location = shader->GetVariable("viewPos");
 //   if(location != -1)
 //       shader->SetFloat3(location,camera->GetPosition().x,camera->GetPosition().y,camera->GetPosition().z);
}

void BaseRender::addLight(Light&light)
{
	_lights.push_back(light);
}

void BaseRender::preRenderShaderData()
{
	glm::mat4 projectionMatrix = camera->GetProjectionMatrix();

	glm::mat4 viewMatrix = camera->GetViewMatrix();

	glBindBuffer(GL_UNIFORM_BUFFER, uboBlock);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &projectionMatrix[0][0]);
	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &viewMatrix[0][0]);
	//glBindBuffer(GL_UNIFORM_BUFFER,0);
}
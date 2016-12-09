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
#include "../include/mesh.h"
#include "../include/sys.h"
#include "../include/log.h"
#include "../include/camera.h"
#include "../include/geometry.h"
#include "../include/texture.h"
#include "../include/Timer.h"
#include "../include/contextMap.h"

#include  <glm/gtc/type_ptr.hpp>
#include "SOIL2/SOIL2.h"

#include <string>
#include <vector>
#include <random>
#include <iostream>

const unsigned int NR_LIGHTS = 32;
///////////////////// Just For This Test//////////////////////////////

 
GLuint pixBufferIds[2]; //two pbo for update texture
GLuint textureID; //the update texture 

GLuint textureBO;

GLuint width = 1024;
GLuint height = 896;

GLuint objId;
GLuint pboMode;

GLvoid*imageData;

const int DATA_SIZE = width * height * 4;
const GLenum PIXEL_FORMAT    = GL_BGRA;

float copyTime, updateTime;
Timer timer, t1, t2;

unsigned testFun = 1;
GLint Scene::_prg_max_sides = -1;
GLint Scene::_prg_tb_blocks = -1;
GLint Scene::_prg_block_type = -1;
GLint Scene::_prg_start_index = -1
	;
GLint Scene::_prg_mvp = -1;

GLuint sceneVBO = 0;

///////////////////////////////////////////////////////////////////
 

glm::vec4 normalize_plane(const glm::vec4 &p) {
	//return p*(1.0f/length(p.swizzle(glm::comp::X,glm::comp::Y,glm::comp::Z)));
    return glm::vec4();
}

void updatePixels(GLubyte* dst, int size)
{
	static int color = 0;

	if(!dst)
		return;

	int* ptr = (int*)dst;

	// copy 4 bytes at once
	for(int i = 0; i < height; ++i)
	{
		for(int j = 0; j < width; ++j)
		{
			*ptr = color;
			++ptr;
		}
		color += 257;   // add an arbitary number (no meaning)
	}
	++color;            // scroll down
}


Scene::Scene()
{
}

void Scene::Initialize()
{
	initOpengl();
	initLight();
	initSceneObjs();
	initShader();
	initTexture();
	initFBO();
	initThisDemo();
}

void Scene::initOpengl(void)
{
	//deafult the GL_CULL_FACE is disable
	//glEnable(GL_CULL_FACE); 
	//glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

}

void Scene::initTexture(void)
{
	 
	 
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
#if defined X_OS_WIN32 || defined X_OS_WIN64 
	shaderBasePath = "D:/projects/opengl/Perfance/Asy/OpenGL/shader/";
#elif  __APPLE__
	shaderBasePath = "/Users/glp/Documents/projects/OpenGL/OpenGL/shader/";
#endif

	if(testFun == 0)
	{
		std::string vs = shaderBasePath + "hdr.vert";
		std::string fs = shaderBasePath + "hdr.frag";

		_shaders.push_back(new Shader());
		_shaders[0]->LoadShaders(vs.c_str(),fs.c_str());

		_shaders[0]->TurnOn();
		GLint textureI = _shaders[0]->GetVariable("hdrBuffer");
		_shaders[0]->SetInt(textureI,0);
		_shaders[0]->TurnOff();
	}
	else if(testFun == 1)
	{
		std::string vs = shaderBasePath + "block_v.glsl";
		std::string fs = shaderBasePath + "block_f.glsl";

		_shaders.push_back(new Shader());
		_shaders[0]->LoadShaders(vs.c_str(),fs.c_str());

		_prg_max_sides = _shaders[0]->GetVariable("max_sides");
		_prg_tb_blocks = _shaders[0]->GetVariable("tb_blocks");
		_prg_block_type =_shaders[0]->GetVariable("block_type");
		_prg_start_index = _shaders[0]->GetVariable("start_index");
		_prg_mvp = _shaders[0]->GetVariable("mvp");

	}
}

void Scene::initSceneObjs(void)
{

#if defined X_OS_WIN32 || defined X_OS_WIN64
	
#elif defined __APPLE__

#endif
	
	if(testFun == 0)
	{
		initScreenQuad(objId);
	}
}

void Scene::Render()
 {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if(testFun == 0)
	{
		Shader * currentShader = _shaders[0];
		currentShader->TurnOn();

		static int index = 0;
		int nextIndex = 0;   

		if(pboMode == 0)
		{
			// cpu -> gpu noraml
			t1.start();
			glBindTexture(GL_TEXTURE_2D,textureID);
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, PIXEL_FORMAT, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
			t1.stop();
			copyTime = t1.getElapsedTimeInMilliSec();

			std::cout << "GPU Milliseconds: " << copyTime << std::endl;

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,textureID);
			drawScreenQuad(objId);
			glBindTexture(GL_TEXTURE_2D,0);
			currentShader->TurnOff();

			//update image Data
			GLfloat timercpu = _query.getCurrentTime();
			updatePixels((GLubyte*)imageData, DATA_SIZE);
			GLfloat timercpu2 = _query.getCurrentTime();

			std::cout << "cpu Milliseconds : "  <<  timercpu2 - timercpu << std::endl;
		}

		//one and two pbo
		else if(pboMode == 1 ||  pboMode == 2)
		{
			if(pboMode == 1)
				index = nextIndex = 0; //single PBO
			else 
			{
				index = (index + 1) % 2; //double PBO
				nextIndex = (index + 1) % 2;
			}

			//update texture 
			t1.start();
			glBindTexture(GL_TEXTURE_2D,textureID);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[index]);
			glTexSubImage2D(GL_TEXTURE_2D,0,0,0,width,height,PIXEL_FORMAT,GL_UNSIGNED_BYTE,NULL);
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
			t1.stop();
			copyTime = t1.getElapsedTimeInMilliSec();
			std::cout << "GPU Milliseconds: " << copyTime << std::endl;

			GLuint64 cpuTimer = _query.getCurrentTime();
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[nextIndex]);
			// map the buffer object into client's memory
			// Note that glMapBufferARB() causes sync issue.
			// If GPU is working with this buffer, glMapBufferARB() will wait(stall)
			// for GPU to finish its job. To avoid waiting (stall), you can call
			// first glBufferDataARB() with NULL pointer before glMapBufferARB().
			// If you do that, the previous data in PBO will be discarded and
			// glMapBufferARB() returns a new allocated pointer immediately
			// even if GPU is still working with the previous data.
			glBufferData(GL_PIXEL_UNPACK_BUFFER,DATA_SIZE,NULL,GL_STREAM_DRAW);
			GLubyte * prt =  (GLubyte*)glMapBuffer(GL_PIXEL_UNPACK_BUFFER,GL_WRITE_ONLY);

			if(prt)
			{
				updatePixels(prt,DATA_SIZE);
				glUnmapBuffer(GL_PIXEL_UNPACK_BUFFER);
			}
			glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
			GLuint64 cpuTimer2 = _query.getCurrentTime();

			std::cout << "update imageData: "  << cpuTimer2 - cpuTimer << std::endl;

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D,textureID);
			drawScreenQuad(objId);
			glBindTexture(GL_TEXTURE_2D,0);
			currentShader->TurnOff();
		}
	}
	
	else if(testFun == 1)
	{
		ContextMap * ct = _contextMapPool[0];

		frustum_check(ct);

		ct->getMapPtr();

		upload_blocks_to_gpu(ct);

		ct->flush_scene_data();

		render_blocks(ct);

		ct->LockBuffer();
	}
}

// This handles all the cleanup for our model, like the VBO/VAO buffers and shaders.
void Scene::Destroy()
{
	for (int i = _shaders.size() - 1; i >= 0; i--)
	{
		Shader * s = _shaders[i];
		s->Destroy();
		s = NULL;
	}

	for(unsigned int i = 0;i < _modes.size();i++)
	{
		delete _modes[i];
		_modes[i] = NULL;
	}

	for(unsigned int i = 0;i < _textures.size();i++)
	{
		glDeleteBuffers(1,&_textures[i]);
	}

	for(unsigned int i = 0;i < _fbos.size();i++)
	{
		glDeleteFramebuffers(1,&_fbos[i]);
	}
}

void Scene::initThisDemo(void)
{
	if(testFun == 0)
	{
		//texture for update
		glGenTextures(1,&textureID);
		glBindTexture(GL_TEXTURE_2D,textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA8,width,height,0,PIXEL_FORMAT,GL_UNSIGNED_BYTE ,NULL);
		glBindTexture(GL_TEXTURE_2D,0);

		//PBO
		glGenBuffers(2,&pixBufferIds[0]);
		//GL_STREAM_DRAW  for texture upload
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[0]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4,NULL,GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,pixBufferIds[1]);
		glBufferData(GL_PIXEL_UNPACK_BUFFER, width * height * 4,NULL,GL_STREAM_DRAW);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

		//imageData for texture
		imageData = new GLubyte[DATA_SIZE];
		memset(imageData, 0, DATA_SIZE);
		//generate Query

		_query.genQueries();

		pboMode= 2;
	}
	else if(testFun == 1)
	{
		glGenBuffers(1,&sceneVBO);
		glBindBuffer(GL_ARRAY_BUFFER,sceneVBO);
		glBufferData(GL_ARRAY_BUFFER,16384*4,0,GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		//prepare contextMap
		createContextMapPool(1,6);

		createSceneData();

	}
}

void Scene::setScreenWH(unsigned int w,unsigned int h)
{
	_screenWidth = w;
	_screenHeight = h;
}

void Scene::createSceneData(void)
{
	const int grid_size = BUILDING_SIDE_SIZE;
	const glm::vec3 pillar_size(0.25f, 2.6f, 0.25f);
	const glm::vec3 box_size(3.0f, 0.2f, 4.0f);

	// create floor's pillars
	for(int z = 0; z < grid_size; ++z)
		for(int y = 0; y < (grid_size >> 1); ++y)
			for(int x = 0; x < grid_size; ++x) 
			{
				if(z < grid_size-1)
				{
					add_block(0, glm::vec3(x * 3, 0.2 + z * 2.8, y * 4), pillar_size, 0);
				}
				add_block(1, glm::vec3(x * 3, z * 2.8, y * 4), box_size, 0);
			}
}

Scene::block* Scene::add_block(const int type, const glm::vec3 &pos, const glm::vec3 &size, const float heading)
{
	const vec3 half_size = size * 0.5f;

	mat4 tm = rotate(mat4(1), heading, vec3(0,0,1));
	mat4 bbox = tm;

	tm[0].x = half_size.x;
	tm[1].y = half_size.y;
	tm[2].z = half_size.z;
	tm[3] = vec4(pos,1);
	_tms.push_back(tm);

	bbox[3] = vec4(pos + vec3(0,half_size.y,0),1);
	_bboxes.push_back(bbox);

	_hws.push_back(size * 0.5f);
	_flags.push_back(type & 3);

	_blocks.push_back(
		block(
		&*(_tms.end()-1),
		&*(_flags.end()-1),
		&*(_hws.end()-1)));

	return &*(_blocks.end()-1);
}

int Scene::frustum_check(ContextMap *ctx,const bool dont_check/*=true*/)
{
	// prepare frustum planes
	const int num_planes=6;
	glm::vec4 planes[num_planes];
	create_frustum_planes(planes,GetCamera()->GetProjectionMatrix() * GetCamera()->GetViewMatrix());

	glm::vec4 * const planes_end=planes+num_planes;

	const mat4 *bbox = &_bboxes[0];
	const vec3 *hw = &_hws[0];
	unsigned int *flags = &_flags[0];
	const unsigned int *e = &_flags[0] + _flags.size();

	memset(ctx->_num_visible_blocks, 0, sizeof(ctx->_num_visible_blocks));

	for( ; flags != e; ++hw, ++bbox, ++flags) {
		const vec4 *plane = planes;
		if(!dont_check) {
			for(; plane != planes_end; ++plane) {
				// transform plane's normal to bbox space
				const glm::vec3 npv(
					dot((*bbox)[0], *plane),
					dot((*bbox)[1], *plane),
					dot((*bbox)[2], *plane));

				// and do standard p/n vertex aabb check
				const float mp = dot((*bbox)[3], *plane);
				const float np = dot(*hw, abs(npv));

				if(mp + np < 0.0f) break;
			}

			*flags = *flags & (~0x04);
		}

		if(plane == planes_end || dont_check) {
			*flags |= 0x04;
			++ctx->_num_visible_blocks[*flags & 3];
		}
	}
 

	return ctx->_num_visible_blocks[0];
}

void Scene::create_frustum_planes(glm::vec4 *planes, const glm::mat4 &mvp)
{
	// Left plane
	planes[0] = normalize_plane(vec4(
		mvp[0].w+mvp[0].x,
		mvp[1].w+mvp[1].x,
		mvp[2].w+mvp[2].x,
		mvp[3].w+mvp[3].x));

	// Right plane
	planes[1]=normalize_plane(vec4(
		mvp[0].w-mvp[0].x,
		mvp[1].w-mvp[1].x,
		mvp[2].w-mvp[2].x,
		mvp[3].w-mvp[3].x));

	// Top plane
	planes[2]=normalize_plane(vec4(
		mvp[0].w-mvp[0].y,
		mvp[1].w-mvp[1].y,
		mvp[2].w-mvp[2].y,
		mvp[3].w-mvp[3].y));

	// Bottom plane
	planes[3]=normalize_plane(vec4(
		mvp[0].w+mvp[0].y,
		mvp[1].w+mvp[1].y,
		mvp[2].w+mvp[2].y,
		mvp[3].w+mvp[3].y));

	// Far plane
	planes[4]=normalize_plane(vec4(
		mvp[0].w-mvp[0].z,
		mvp[1].w-mvp[1].z,
		mvp[2].w-mvp[2].z,
		mvp[3].w-mvp[3].z));

	// Near plane
	planes[5]=normalize_plane(vec4(
		mvp[0].z,mvp[1].z,mvp[2].z,mvp[3].z));
}

void Scene::upload_blocks_to_gpu(ContextMap *ctx)
{
	ctx->_scene_data_ptr_size = 0;
	for(int i = 0; i < 4; ++i)
		ctx->_scene_data_ptr_size += ctx->_num_visible_blocks[i];
	ctx->_scene_data_ptr_size *= sizeof(mat4);

	if(ctx->_scene_data_ptr_size > 0)
	{
		mat4 *ptr[4];

		ptr[0] = ctx->_scene_data_ptr;

		if(ptr[0] == 0)
		{
			return;
		}

		for(int i = 1; i < 4; ++i)
			ptr[i] = ptr[i - 1] + ctx->_num_visible_blocks[i - 1];

		const mat4 *tm = &_tms[0];
		const mat4 *e = &_tms[0] + _tms.size();
		unsigned int *flags = &_flags[0];

		// transform visible blocks to screen and add to VBO 
		for(; tm!=e; ++tm, ++flags)
			if(*flags & 0x04)
				*ptr[*flags & 3]++ = /*ctx->_mvp * */(*tm);
	}
}

void Scene::render_blocks(const ContextMap *ctx)
{
	Shader * currentShader = _shaders[0];
	currentShader->TurnOn();

	glBindBuffer(GL_ARRAY_BUFFER,sceneVBO);
	glVertexAttribPointer(0,4,GL_BYTE,GL_FALSE,0,0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glEnableVertexAttribArray(0);

	glUniform1f(_prg_max_sides, float(64));
	glUniform1i(_prg_block_type, 0);
	glUniform1i(_prg_start_index, 0);
	glUniformMatrix4fv(_prg_mvp, 1, GL_FALSE, glm::value_ptr(GetCamera()->GetProjectionMatrix() * GetCamera()->GetViewMatrix() ));

	glUniform1i(_prg_tb_blocks, 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_BUFFER, ctx->_scene_tb);

	const int batch_size = 100;

	if(ctx->_num_visible_blocks[0]>0) 
	{
		int pos = 0;
		glUniform1i(_prg_start_index, pos);
		glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, (64 << 1) + 2, ctx->_num_visible_blocks[0]);
	}

	if(ctx->_num_visible_blocks[1])
	{
		glUniform1i(_prg_block_type, 1);
		int pos = 0 + ctx->_num_visible_blocks[0];
		glUniform1i(_prg_start_index, pos);
		glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, 8, ctx->_num_visible_blocks[1] << 1);
	}

	if(ctx->_num_visible_blocks[2])
	{
		glUniform1i(_prg_block_type, 2);
		glUniform1i( _prg_start_index, 0  + ctx->_num_visible_blocks[0] 
		+ ctx->_num_visible_blocks[1]);

		glDrawArraysInstanced( GL_TRIANGLE_STRIP, 0, 20 * 4, ctx->_num_visible_blocks[2] << 1);
	}   

	glDisableVertexAttribArray(0);

	currentShader->TurnOff();
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

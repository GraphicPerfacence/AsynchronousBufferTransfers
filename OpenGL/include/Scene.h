//
//  Model.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__Model__
#define __OpenGL__Model__

#include "BaseRender.h"
#include "GLQuery.h"
#include "math3d.h"
#include <stdio.h>

class INode;
class ContextMap;

class Scene :public BaseRender
{
public:

	static const int BUILDING_SIDE_SIZE = 32;
	static const int MAX_BLOCK_COUNT = BUILDING_SIDE_SIZE * (BUILDING_SIDE_SIZE >> 1) * BUILDING_SIDE_SIZE * 2;

	struct block
	{
		glm::mat4 *_tm;
		unsigned int *_flags;
		glm::vec3 *_hw;

		block(
			glm::mat4 *tm,
			unsigned int *flags,
			glm::vec3 *hw)
			: _tm(tm)
			, _flags(flags)
			, _hw(hw)
		{}
	};


	// Set the scale of our model to 100% by default
	Scene();
	~Scene() { Destroy(); }

	void Initialize();
	void initShader(void);
	void initSceneObjs(void);
	void initLight(void);
	void initFBO(void);
	void initBOs(unsigned int size);
	void initTexture(void);
	void initOpengl(void);
	void initThisDemo(void);

	
	//添加测试场景模型用来测试
	void createSceneData(void);
	block* add_block( const int type, const glm::vec3 &pos, const glm::vec3 &size, const float heading);
	int frustum_check(ContextMap *fc,const bool dont_check=true);
	void create_frustum_planes(glm::vec4 *planes, const glm::mat4 &mvp);
	void upload_blocks_to_gpu(ContextMap *ctx);
	void render_blocks(const ContextMap *ctx);


	// This draws the Model to the backbuffer
	void Render();

	// Create the getter and setters for the model's position
	Vec3f GetPosition() { return Position; }
	void SetPosition(Vec3f position) { Position = position; }

	// Create the getter and setters for the model's rotation
	Vec3f GetRotation() { return Rotation; }
	void SetRotation(Vec3f rotation) { Rotation = rotation; }

	// Create the getter and setters for the model's scale
	Vec3f GetScale() { return Scale; }
	void SetScale(Vec3f scale) { Scale = scale; }

	void setScreenWH(unsigned int w,unsigned int h);

	void Destroy();

protected:

	unsigned int bufferNum;

	unsigned int _screenWidth;
	unsigned int _screenHeight;

	Vec3f        Position;										// The model's position
	Vec3f        Rotation;										// The model's rotation
	Vec3f        Scale;											// The model's scale

	std::vector<INode*> _modes;
	std::vector<unsigned int> _fbos; // framebuffer object;
	std::vector<unsigned int> _textures; //texture objects

	GLQuery _query;

	//blower is juest for createSceneData
	std::vector<glm::mat4> _tms;			//< transformation matrixes for blocks
	std::vector<glm::mat4> _bboxes;			//< inverse transposed TM matrices
	std::vector<glm::vec3> _hws;			//< half width for every block
	std::vector<unsigned int> _flags;		//<

	typedef std::vector<block> blocks_t;
	blocks_t _blocks;
	static GLint _prg_max_sides;
	static GLint _prg_tb_blocks;
	static GLint _prg_block_type;
	static GLint _prg_start_index;
	static GLint _prg_mvp;


};


#endif /* defined(__OpenGL__Model__) */

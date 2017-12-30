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
#include "XGLQuery.h"

#include <stdio.h>
#include <glm/glm.hpp>

class Scene :public BaseRender
{
public:

	static const int BUILDING_SIDE_SIZE = 32;
	static const int MAX_BLOCK_COUNT = BUILDING_SIDE_SIZE *
            (BUILDING_SIDE_SIZE >> 1) * BUILDING_SIDE_SIZE * 2;

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


	// This draws the Model to the backbuffer
	void Render();

    void Destroy();

protected:

	unsigned int bufferNum;

	std::vector<unsigned int> _fbos; // framebuffer object;

	XGLQuery _query;


	//blower is juest for createSceneData
	std::vector<glm::mat4> _tms;			//< transformation matrixes for blocks
	std::vector<glm::mat4> _bboxes;			//< inverse transposed TM matrices
	std::vector<glm::vec3> _hws;			//< half width for every block
	std::vector<unsigned int> _flags;		//<

	static GLint _prg_max_sides;
	static GLint _prg_tb_blocks;
	static GLint _prg_block_type;
	static GLint _prg_start_index;
	static GLint _prg_mvp;

};


#endif /* defined(__OpenGL__Model__) */

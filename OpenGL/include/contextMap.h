
//
//  contextMap.h
//  OpenGL
//
//  Created by xt on 7/12/16
//  Copyright (c) 2016Äê xt. All rights reserved.
//

#include "glm/glm.hpp"
#include "GL/glew.h"
#include <vector>

struct batch
{
	glm::vec2 pos;
	glm::vec2 size;
	int index;
	int count;
	unsigned tex;

	batch(
		const glm::vec2 &pos,
		const glm::vec2 &size,
		const int index,
		const int count,
		const int tex)
		: pos(pos)
		, size(size)
		, index(index)
		, count(count)
		, tex(tex)
	{}
};

typedef std::vector<batch> batches_t;

enum Mode 
{
	ModeInvalidateBuffer,
	ModeFlushExplicit,
	ModeUnsynchronized, 
	ModeBufferData,
	ModeBufferSubData,
	ModeWrite,
};

struct ContextMap
{
	static const int POOL_SIZE;

	ContextMap();

	Mode _mode;

	unsigned _scene_vbo;
	unsigned _scene_tb;

	glm::mat4* _scene_data_ptr;
	unsigned _scene_data_ptr_size;

	int _num_visible_blocks[4];

	void map_scene();

	void flush_scene_data();

	void create_buffers();

	void put_fence();
	bool check_fence();

	GLsync _fence;
	bool first;

	bool _persistent;
};

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

enum ContextMapMode 
{
	ModeInvalidateBuffer,
	ModeFlushExplicit,
	ModeUnsynchronized, 
	ModeBufferData,
	ModeBufferSubData,
	ModeWrite,
	ModePersistent
};

struct PersistentBufferRange
{
	PersistentBufferRange()
	{
		_begin = 0;
		_sync = 0;
	}
	size_t _begin;
	GLsync _sync;
};

struct ContextMap
{

	ContextMap();

	~ContextMap();

	ContextMapMode _mode;

	unsigned _scene_vbo;
	unsigned _scene_tb;

	glm::mat4* _scene_data_ptr;
	glm::mat4 * _persistentRangeMapStartPtr;

	unsigned _scene_data_ptr_size;

	int _num_visible_blocks[4];

	void getMapPtr();

	void flush_scene_data();

	void create_buffers(ContextMapMode flag);

	void WaitBuffer(void);
	void LockBuffer(void);
	void LockBuffer(GLsync& syncObj);
	void WaitBuffer(GLsync& syncObj);

	PersistentBufferRange gSyncRanges[3]; //now persisten use 3 section
	GLuint gPersistentRangeIndex;
};
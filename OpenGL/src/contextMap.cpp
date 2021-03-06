
#include "../include/contextMap.h"
#include "../include/Scene.h"
#include "../include/log.h"

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


void ContextMap::getMapPtr()
{
	if(ModePersistentCoheren == _mode || ModePersistentFlush == _mode)
	{
		WaitBuffer(gSyncRanges[gPersistentRangeIndex]._sync);

		size_t startID = gSyncRanges[gPersistentRangeIndex]._begin;

		_scene_data_ptr = _persistentRangeMapStartPtr + startID;
	}
	
	else if (ModeUnsynchronized == _mode)
	{
		glBindBuffer(GL_TEXTURE_BUFFER, _scene_vbo);
		_scene_data_ptr = reinterpret_cast<glm::mat4*>(glMapBufferRange(GL_TEXTURE_BUFFER,0,
			Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4), GL_MAP_UNSYNCHRONIZED_BIT | GL_MAP_WRITE_BIT));
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}
	else if (ModeInvalidateBuffer == _mode)
	{
		glBindBuffer(GL_TEXTURE_BUFFER, _scene_vbo);
		_scene_data_ptr = reinterpret_cast<glm::mat4*>(
			glMapBufferRange(
				GL_TEXTURE_BUFFER,0,
				Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4),
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT));
		glBindBuffer(GL_TEXTURE_BUFFER, 0);

		_scene_data_ptr_size = 0;
	}
	else if (ModeUnsynchronized == _mode)
	{
		if (gSyncRanges[0]._sync != 0)
		{
			WaitBuffer(gSyncRanges[0]._sync);
		}

		glBindBuffer(GL_TEXTURE_BUFFER, _scene_vbo);
		_scene_data_ptr = reinterpret_cast<glm::mat4*>(
			glMapBufferRange(
				GL_TEXTURE_BUFFER,
				0,
				Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4),
				GL_MAP_WRITE_BIT | GL_MAP_UNSYNCHRONIZED_BIT));

		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}

	else if (ModeBufferSubData == _mode)
	{
		if (!_scene_data_ptr)
			_scene_data_ptr = new glm::mat4[Scene::MAX_BLOCK_COUNT];
		_scene_data_ptr_size = 0;
	}
}

/************************************************************************/
/* flag 0: Persistent                                            */
/************************************************************************/

void ContextMap::create_buffers(unsigned int model)
{
	glGenBuffers(1,&_scene_vbo); //texture buffer object

	glBindBuffer(GL_TEXTURE_BUFFER,_scene_vbo);

	_mode = (ContextMapMode)model;

	if(model == ModePersistentCoheren || model == ModePersistentFlush)
	{
		gPersistentRangeIndex = 0;
		
		gSyncRanges[0]._begin = 0; //for 3 sections and every section start point
		gSyncRanges[1]._begin = Scene::MAX_BLOCK_COUNT ;
		gSyncRanges[2]._begin = Scene::MAX_BLOCK_COUNT  * 2;
		
		if (ModePersistentCoheren == model)
		{
			GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;

			glBufferStorage(GL_TEXTURE_BUFFER, Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4) * 3, 0, flags);

			_scene_data_ptr = reinterpret_cast<glm::mat4*>(glMapBufferRange(GL_TEXTURE_BUFFER, 0,
				Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4) * 3, flags));
		}
		else
		{
			GLbitfield flags = GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT;

			glBufferStorage(GL_TEXTURE_BUFFER, Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4) * 3, 0, flags);

			_scene_data_ptr = reinterpret_cast<glm::mat4*>(glMapBufferRange(GL_TEXTURE_BUFFER, 0,
				Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4) * 3, flags | GL_MAP_FLUSH_EXPLICIT_BIT));
		}

		_persistentRangeMapStartPtr = _scene_data_ptr;
	}
	else if(ModeUnsynchronized == _mode)
	{
		gSyncRanges[0]._begin = 0;
		glBufferData(GL_TEXTURE_BUFFER, Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4), 0, GL_STREAM_DRAW);
	}
	else
	{
		glBufferData(GL_TEXTURE_BUFFER, Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4), 0, GL_STREAM_DRAW);
	}
	
	glGenTextures(1, &_scene_tb);
	glBindTexture(GL_TEXTURE_BUFFER,_scene_tb);
	glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA32F,_scene_vbo);
	glBindBuffer(GL_TEXTURE_BUFFER,0);

}

void ContextMap::flush_scene_data()
{
	if(ModePersistentCoheren == _mode || ModePersistentFlush == _mode)
	{
		if (ModePersistentFlush == _mode)
		{
			glFlushMappedBufferRange(GL_TEXTURE_BUFFER, gSyncRanges[gPersistentRangeIndex]._begin * sizeof(glm::mat4),
				Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4));
		}
		//next section index
		glBindBuffer(GL_TEXTURE_BUFFER,_scene_tb);

		glTexBufferRange(GL_TEXTURE_BUFFER,GL_RGBA32F,_scene_vbo,
			gSyncRanges[gPersistentRangeIndex]._begin * sizeof(glm::mat4),
			Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4));
		
		glBindBuffer(GL_TEXTURE_BUFFER,0);

	}
	else if(ModeBufferSubData == _mode)
	{
		glBindBuffer(GL_TEXTURE_BUFFER, _scene_vbo);
		glBufferSubData(GL_TEXTURE_BUFFER, 0, _scene_data_ptr_size, _scene_data_ptr);
		glBindBuffer(GL_TEXTURE_BUFFER, 0);
	}
	else 
	{
		glBindBuffer(GL_TEXTURE_BUFFER,_scene_vbo);
		glUnmapBuffer(GL_TEXTURE_BUFFER);
		glBindBuffer(GL_TEXTURE_BUFFER,0);
	}

}

ContextMap::ContextMap()
{
	_scene_data_ptr = NULL;
	_persistentRangeMapStartPtr = NULL;
}

ContextMap::~ContextMap()
{

	if(ModePersistentCoheren == _mode)
	{
		glUnmapBuffer(GL_TEXTURE_BUFFER);
	}

	if(_scene_vbo != 0)
	{
		glDeleteBuffers(1,&_scene_vbo);
	}
	if(_scene_tb != 0)
	{
		glDeleteTextures(1,&_scene_tb);
	}
}

void ContextMap::LockBuffer(GLsync& syncObj)
{
	if(syncObj)
		glDeleteSync(syncObj);

	syncObj = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE ,0);
}

void ContextMap::LockBuffer(void)
{
	if (ModePersistentCoheren == _mode || ModePersistentFlush == _mode)
	{
		LockBuffer(gSyncRanges[gPersistentRangeIndex]._sync);
		gPersistentRangeIndex = (gPersistentRangeIndex + 1) % 3;
	}
	else if (ModeUnsynchronized == _mode)
	{
		LockBuffer(gSyncRanges[0]._sync);
	}
}

void ContextMap::WaitBuffer(GLsync& syncObj)
{
	if(syncObj)
	{
		while(1)
		{
			GLenum waitReturn = glClientWaitSync(syncObj,GL_SYNC_FLUSH_COMMANDS_BIT,1);
			if (waitReturn == GL_ALREADY_SIGNALED || waitReturn == GL_CONDITION_SATISFIED)
				return;
		}
	}
}

void ContextMap::WaitBuffer(void)
{
	WaitBuffer(gSyncRanges[gPersistentRangeIndex]._sync);
}

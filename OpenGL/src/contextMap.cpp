
#include "../include/contextMap.h"
#include "../include/Scene.h"

void ContextMap::map_scene()
{
	glBindBuffer(GL_TEXTURE_BUFFER,_scene_vbo);
	 
	_scene_data_ptr = reinterpret_cast<glm::mat4*>(glMapBufferRange(GL_TEXTURE_BUFFER,0,
		Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4),GL_MAP_WRITE_BIT));

	glBindBuffer(GL_TEXTURE_BUFFER,0);
}

void ContextMap::create_buffers()
{
	glGenBuffers(1,&_scene_vbo); //texture buffer object
	glBindBuffer(GL_TEXTURE_BUFFER,_scene_vbo);
	glBufferData(GL_TEXTURE_BUFFER, Scene::MAX_BLOCK_COUNT * sizeof(glm::mat4), 0, GL_STREAM_DRAW);
	glBindBuffer(GL_TEXTURE_BUFFER,0);

	glGenTextures(1,&_scene_tb);
	glBindBuffer(GL_TEXTURE_BUFFER,_scene_tb);
	glTexBuffer(GL_TEXTURE_BUFFER,GL_RGBA,_scene_vbo);
	glBindBuffer(GL_TEXTURE_BUFFER,0);


	if(_persistent)
	{

	}
}

void ContextMap::flush_scene_data()
{
	glBindBuffer(GL_TEXTURE_BUFFER,_scene_vbo);


	glUnmapBuffer(GL_TEXTURE_BUFFER);

	glBindBuffer(GL_TEXTURE_BUFFER,0);
}

bool ContextMap::check_fence()
{
	return false;
}

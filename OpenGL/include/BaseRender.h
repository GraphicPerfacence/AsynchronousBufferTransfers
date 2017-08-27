//
//  BaseRender.h
//  
//
//  Created by xt on 16/1/31.
//
//

#ifndef ____BaseRender__
#define ____BaseRender__

#include <stdio.h>
#include <vector>
#include "texture.h"

class Shader;
class Camera;

class BaseRender
{

public:
	BaseRender();
	~BaseRender();


	Camera *            GetCamera()const;
	void                SetCamera(Camera *pCamera);

protected:

	void                initUniformVal(Shader*shader,bool modelNeed = true);
	void                preRenderShaderData();
	void                createContextMapPool(unsigned int cout, unsigned int flag);

protected:

	Camera *                    _camera;
	int                         _uboBlock;
	std::vector<TextureObj*>    _texturesObj;
	std::vector<Shader*>        _shaders;
};
#endif /* defined(____BaseRender__) */

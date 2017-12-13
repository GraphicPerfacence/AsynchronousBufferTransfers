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
#include "CameraEx.h"

class Shader;


class BaseRender
{

public:
	BaseRender();
	~BaseRender();


	CameraEx<float> *            GetCamera()const;
	void                SetCamera(CameraEx<float> *pCamera);

protected:

	void                initUniformVal(Shader*shader,bool modelNeed = true);
	void                preRenderShaderData();
	void                createContextMapPool(unsigned int cout, unsigned int flag);

protected:

	CameraEx<float> *                    _camera;
	int                         _uboBlock;
	std::vector<TextureObj*>    _texturesObj;
	std::vector<Shader*>        _shaders;
};
#endif /* defined(____BaseRender__) */

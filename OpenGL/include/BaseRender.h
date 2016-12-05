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
#include "Light.h"
#include "texture.h"

class Shader;
class Camera;


class BaseRender
{

public:
	BaseRender();
	// This gets and sets the camera to get access to the view and projection matrices
	Camera *GetCamera() { return camera; }
	void SetCamera(Camera *pCamera)
	{
		camera = pCamera;
	}

	void addLight(Light&light);

protected:
	void initUniformVal(Shader*shader);
	void preRenderShaderData();
protected:

	Camera *       camera;
	int         uboBlock;
	std::vector<Light> _lights;
	std::vector<Texture> _texturesObj;

protected:
	std::vector<Shader*>        shaders;
};
#endif /* defined(____BaseRender__) */

//
//  Inputmanager.cpp
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//



#include "../include/Inputmanager.h"
#include "../include/TimerManager.h"

//test shader uniform 
extern float g_gamma;

extern void modelInput(InputCodes code);

void InputManager::KeyPressed(InputCodes code)
{
	if (_camera == nullptr)
		return;

    switch (code)
	{

	case InputCodes::W: case InputCodes::w:
		_camera->ProcessKeyboard(Camera::FORWARD,TimeManager::Instance().DeltaTime);
		break;

	case InputCodes::S: case InputCodes::s:
		_camera->ProcessKeyboard(Camera::BACKWARD, TimeManager::Instance().DeltaTime);
		break;

	case Left: case InputCodes::a:
		_camera->ProcessKeyboard(Camera::LEFT, TimeManager::Instance().DeltaTime);
		break;
	
	case Right: case InputCodes::D: case InputCodes::d:
		_camera->ProcessKeyboard(Camera::RIGHT, TimeManager::Instance().DeltaTime);
		break;
	}
	modelInput(code);
}


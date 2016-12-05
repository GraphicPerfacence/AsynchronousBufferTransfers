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
	// If there isn't a camera specified, just return
	if (Camera == nullptr)
		return;

	// Depending on the code, move the camera back or forward fixed by a speed and time slice
	// to make sure the movement is the same on anyone's computer regardless of the speed.
	switch (code)
	{
		// If the user moves up, move the camera up along the view vector
	case InputCodes::W: case InputCodes::w:
		Camera->MoveCamera(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;
		// If the user moved down, move the camera down along the view vector
	case InputCodes::S: case InputCodes::s:
		Camera->MoveCamera(-1 * Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;

	case Left: 
		Camera->Strafe(-1 * Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;
		// If the user hits the RIGHT or D key, strafe the camera to the right
	case Right: case InputCodes::D: case InputCodes::d:
		Camera->Strafe(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;

	case Up:
		Camera->Strafe(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;
	case Down:
		Camera->Strafe(Camera->GetSpeed() * TimeManager::Instance().DeltaTime);
		break;
	}
	modelInput(code);
}


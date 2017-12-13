    //
    //  Inputmanager.cpp
    //  OpenGL
    //
    //  Created by xt on 15/8/10.
    //  Copyright (c) 2015年 xt. All rights reserved.
    //

#include "Inputmanager.h"
#include "TimerManager.h"

#include <string.h>
#include <GLFW/glfw3.h>

extern void modelInput(InputCodes code);

void  InputManager::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    if (action == GLFW_PRESS)
        {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        int width, height;
        glfwGetWindowSize(window, &width, &height);

        }
    else if (action == GLFW_RELEASE)
        {


        }
    else if (action == GLFW_REPEAT)
        {

        }

}

void InputManager:: mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse)
{

}

void InputManager::mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos)
{

}

void InputManager::KeyPressed(InputCodes code)
{
    if (_camera == nullptr)
        return;
    switch (code)
    {

        case InputCodes::W: case InputCodes::w:
       _cameraMoveVec =  _camera->processKeyboard(CameraEx<float>::FORWARD,TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::S: case InputCodes::s:
       _cameraMoveVec =   _camera->processKeyboard(CameraEx<float>::BACKWARD, TimeManager::Instance().DeltaTime);
        break;

        case Left: case InputCodes::a:
        _cameraMoveVec =  _camera->processKeyboard(CameraEx<float>::LEFT, TimeManager::Instance().DeltaTime);
        break;
        
        case Right: case InputCodes::D: case InputCodes::d:
        _cameraMoveVec = _camera->processKeyboard(CameraEx<float>::RIGHT, TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::Up:
        _cameraMoveVec =  _camera->processKeyboard(CameraEx<float>::UP, TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::Down:
        _cameraMoveVec =  _camera->processKeyboard(CameraEx<float>::DOWN, TimeManager::Instance().DeltaTime);
        break;
    }
    modelInput(code);

}

void InputManager::UpdateCamera()
{
    _camera->updatePosition(_cameraMoveVec, TimeManager::Instance().DeltaTime);
}

InputManager& InputManager::Instance()
{
    static  InputManager  _singleInstance;

    return  _singleInstance;
}

void InputManager::ClearMoveVec()
{
    _cameraMoveVec.x = _cameraMoveVec.y = _cameraMoveVec.z = 0.0;
}

InputManager::InputManager(){}

InputManager::InputManager(const InputManager&)
{}

InputManager& InputManager::operator=(const InputManager&i)
{
    *this = i;
    return  *this;
}

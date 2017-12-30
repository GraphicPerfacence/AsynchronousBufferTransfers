    //
    //  Inputmanager.cpp
    //  OpenGL
    //
    //  Created by xt on 15/8/10.
    //  Copyright (c) 2015年 xt. All rights reserved.
    //

#include "Inputmanager.h"
#include "TimerManager.h"
#include "camera.h"

#include <string.h>
#include <GLFW/glfw3.h>


bool g_mouseLeftDown    = false;
bool g_mouseLeftRelease = false;
bool g_mouseRightDown   = false;
bool g_mouseMiddleDown  = false;
bool g_mouseLeftDown_first = true;

static Camera * _innerCamera = 0;

void  mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{

    if (action == GLFW_PRESS)
        {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
            {
            g_mouseLeftDown = true;
            g_mouseLeftDown_first = true;
            g_mouseLeftRelease = false;
            }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
            {
            g_mouseRightDown = true;
            }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
            g_mouseMiddleDown = true;
            }
        }
    else if (action == GLFW_RELEASE)
        {

        if(button == GLFW_MOUSE_BUTTON_LEFT)
            {
            g_mouseLeftDown = false;
            g_mouseLeftRelease = true;
            g_mouseLeftDown_first = false;
            }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
            {
            g_mouseRightDown = false;
            }
        else if(button == GLFW_MOUSE_BUTTON_MIDDLE)
            {
            g_mouseMiddleDown = false;
            }


        }
    else if (action == GLFW_REPEAT)
        {

        }
}

void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
    if(g_mouseLeftDown)
        {
        if(_innerCamera)
            {
            }


        }
    else if (g_mouseMiddleDown)
        {

        }
    else if(g_mouseRightDown)
        {

        }
}

void  mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse)
{

}

//st GL_PRESS GL_RELEASE GL_REPEAT
void  key_callback(GLFWwindow*window,int key,int code,int st,int mods)
{
    InputManager::Instance()->KeyPressed(key,st,mods);
}

void windowSize(GLFWwindow*window, int width, int height)
{
    glViewport(0, 0, width, height);

    _innerCamera->SetWindowSize(width, height);
}

void InputManager::MouseProcess()
{
    if(g_mouseLeftDown)
    {
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        if(g_mouseLeftDown_first)
        {
            g_mouseLeftDown_first = false;
            _camera->ProcessMouseMovement(Camera::LEFT_BUTTON, Camera::PRESS, xpos,ypos );
        }
        else
        {
            _camera->ProcessMouseMovement(Camera::LEFT_BUTTON, Camera::DRAG, xpos,ypos );
        }
    }
    if(g_mouseLeftRelease)
    {
        g_mouseLeftRelease = false;
        double xpos, ypos;
        glfwGetCursorPos(_window, &xpos, &ypos);
        _camera->ProcessMouseMovement(Camera::LEFT_BUTTON, Camera::RELEASE, xpos,ypos );
    }
}

void InputManager::KeyPressed( int key,int st,int mods)
{
    if (_camera == nullptr)
        return;

    InputCodes ic = InputCodes::Invalid;

    if(key == GLFW_KEY_W) ic = InputCodes::w;
    if(key == GLFW_KEY_A) ic = InputCodes::a;
    if(key == GLFW_KEY_D) ic = InputCodes::d;
    if(key == GLFW_KEY_S) ic = InputCodes::s;
    if(key == GLFW_KEY_P) ic = InputCodes::p;
    
    Camera::Camera_Key_Action ka;

    if(st == GLFW_PRESS)   ka = Camera::KEY_PRESS;
    if(st == GLFW_RELEASE) ka = Camera::KEY_RELEASE;
    if(st == GLFW_REPEAT)  ka = Camera::KEY_RELEASE;

    if(ic == InputCodes::Invalid) return;

    switch (ic)
    {

        case InputCodes::W: case InputCodes::w:
        _camera->ProcessKeyboard(Camera::FORWARD,ka,TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::S: case InputCodes::s:
        _camera->ProcessKeyboard(Camera::BACKWARD, ka,TimeManager::Instance().DeltaTime);
        break;

        case Left: case InputCodes::a:
        _camera->ProcessKeyboard(Camera::LEFT, ka,TimeManager::Instance().DeltaTime);
        break;

        case Right: case InputCodes::D: case InputCodes::d:
        _camera->ProcessKeyboard(Camera::RIGHT,ka, TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::Up:
        _camera->ProcessKeyboard(Camera::UP, ka,TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::Down:
        _camera->ProcessKeyboard(Camera::DOWN,ka, TimeManager::Instance().DeltaTime);
        break;

        case InputCodes::p: case InputCodes::P:
        {
            GLint polygonMode;
            glGetIntegerv(GL_POLYGON_MODE, &polygonMode);
            if(GL_LINE != polygonMode)
            {
                glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
            }

            else
            {
                glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
            }
        }

        break;
    }
    
}

void InputManager::SetCamera(Camera *pCamera)

{
    _camera = pCamera;
    _innerCamera = _camera;
}

InputManager* InputManager::_inputManager = NULL;
Camera*  InputManager::_camera = NULL;
GLFWwindow* InputManager::_window = NULL;

InputManager* InputManager::Instance()
{
    if(_inputManager == NULL)
    {
        _inputManager =  new InputManager;
    }
    return _inputManager;
}

InputManager::InputManager()
{
}


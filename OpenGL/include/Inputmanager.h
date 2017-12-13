//
//  Inputmanager.h
//  OpenGL
//
//  Created by xt on 15/8/10.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__Inputmanager__
#define __OpenGL__Inputmanager__

#define GLM_FORCE_RADIANS								// Make sure GLM is using radians instead of degrees

#include "CameraEx.h"
#include "base/defType.hpp"

// Used to send the input commands to the camera
using namespace glm;									// Set the glm namespace for our vector/matrix functions


enum InputCodes
{
	kEscape = 27,
	Space = 32,
	Left = 37,
	Up = 38,
	Right = 39,
	Down = 40,
	a = 97, A = 65,
	b = 98, B = 66,
	c = 99, C = 67,
	d = 100, D = 68,
	e = 101, E = 69,
	f = 102, F = 70,
	g = 103, G = 71,
	h = 104, H = 72,
	i = 105, I = 73,
	j = 106, J = 74,
	k = 107, K = 75,
	l = 108, L = 76,
	m = 109, M = 77,
	n = 110, N = 78,
	o = 111, O = 79,
	p = 112, P = 80,
	q = 113, Q = 81,
	r = 114, R = 82,
	s = 115, S = 83,
	t = 116, T = 84,
	u = 117, U = 85,
	v = 118, V = 86,
	w = 119, W = 87,
	x = 120, X = 88,
	y = 121, Y = 89,
	z = 122, Z = 90,
};

class GLFWwindow;
// This manager takes care of any input from the user and sent to the camera.  In this tutorials
// we just use the UP and DOWN arrow keys to show moving the camera.
class InputManager
{
public:

    static InputManager& Instance();

	void                    KeyPressed(InputCodes code);

    void                    SetCamera(CameraEx<float> *pCamera) { _camera = pCamera; }
	CameraEx<float> *       GetCamera() { return _camera; }

    //mouse
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse);
    static void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos);

    void                    UpdateCamera();
    void                    ClearMoveVec();
protected:
    InputManager();
    InputManager(const InputManager&);
    InputManager& operator=(const InputManager&);

    Vector3<float>          _cameraMoveVec;
    CameraEx<float> *       _camera;
};

#endif /* defined(__OpenGL__Inputmanager__) */

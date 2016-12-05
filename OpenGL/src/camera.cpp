//
//  camer.cpp
//  OpenGL
//
//  Created by xt on 15/8/9.

//  Copyright (c) 2015ƒÍ xt. All rights reserved.


#include "../include/camera.h"
#include <GLFW/glfw3.h>

static Camera * camera;
static bool btnPress = false;

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (!window || !camera) return;
	if (action == GLFW_PRESS)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		camera->PressBtn(xpos, ypos, width, height, button, glfwGetTime());

		btnPress = true;
	}
	else if (action == GLFW_RELEASE)
	{
		camera->ReleaseBtn(button, glfwGetTime());
		btnPress = false;
	}
	else if (action == GLFW_REPEAT)
	{

	}

}
void mouse_curse_pos_callback(GLFWwindow *window, double xpos, double ypos)
{
	if (!window || !camera) return;
	if (btnPress)
	{
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		int width, height;
		glfwGetWindowSize(window, &width, &height);

		int btn;

		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) btn = GLFW_MOUSE_BUTTON_LEFT;
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) btn = GLFW_MOUSE_BUTTON_RIGHT;
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) == GLFW_PRESS) btn = GLFW_MOUSE_BUTTON_MIDDLE;

		camera->trackMotion(btn, xpos, ypos, width, height, glfwGetTime());
	}

}
void mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse)
{
	camera->MoveCamera(yoffse);
}

Camera::Camera()
{
	_distance = 0.0;

	RotationSpeed = 2;
	MouseSpeed = 0.001;
	axis[0] = 1.0;
	axis[1] = axis[2] = 0.0;
	angle = 0.0;

	camera = this;
}

glm::mat4 Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	// Create the projection matrix with GLM's perspective function, replacing gluPerspective.
	_projectionMatrix = glm::perspective(fov, aspectRatio, nearPlane, farPlane);

	return _projectionMatrix;
}

void Camera::PositionCamera(float positionX, float positionY, float positionZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ) {


	glm::vec3 eye(positionX, positionY, positionZ);
	glm::vec3 center(centerX, centerY, centerZ);
	glm::vec3 up(upX, upY, upZ);

	glm::vec3 f = glm::normalize(center - eye);
	glm::vec3 s = glm::normalize(glm::cross(f, glm::vec3(upX, upY, upZ)));
	glm::vec3 u = glm::cross(s, f);

	_rotate = glm::mat4(s[0], u[0], -f[0], 0.0f,
		s[1], u[1], -f[1], 0.0f,
		s[2], u[2], -f[2], 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);

	_rotate = glm::inverse(_rotate);

	_distance = glm::length((center - eye));

	_center = center;


}

glm::mat4 Camera::GetViewMatrix()
{
	return  glm::translate(glm::vec3(0,0,-_distance)) *
				GetRotationMatrix() * 
				glm::translate( -_center) ;
}

// This returns the current view vector (the direction the camera is looking) from the rotation matrix
glm::vec3 Camera::GetView()
{
	// Since we don't store a view vector, we need to calculate the view vector by taking
	// the inverse of our rotation matrix multiplied by a vector looking down the negative
	// z-axis.  By taking the inverse of our rotation matrix and initial view vector, this
	// essentially gives us the vector that would have been used to create the current matrix.
	// So this essentially gives us a unit vector (length of 1) that represents the direction
	// the camera is looking at.
	glm::vec4 viewVector = glm::inverse(GetRotationMatrix()) * glm::vec4(0, 0, -1, 1);

	// We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
	return glm::vec3(viewVector);
}

glm::vec3 Camera::GetPosition()
{
	glm::translate(glm::vec3(0,0,-_distance)) *
				GetRotationMatrix() *
				glm::translate( -_center) ;
	
	glm::mat4 rotMatrix = glm::translate(_center) * _rotate * glm::translate(glm::vec3(0,0,_distance));
	glm::vec4 pos = rotMatrix * glm::vec4(0,0,0,1);
	
	return glm::vec3(pos.x,pos.y,pos.z);
}
// This returns the camera's up vector (the direction pointing up) from the rotation matrix
glm::vec3 Camera::GetUp()
{
	// Just like we abstracted the view vector from our rotation matrix, we do the same
	// thing to get the up vector but instead change the vector to a vector pointing up.
	// By taking the inverse of the rotation matrix multiplied by a default up vector,
	// it will give us the current up vector of the camera.  The up vector will always
	// be vec3(0, 1, 0) until our next tutorial since we aren't looking up or down yet.
	glm::vec4 upVector = glm::inverse(GetRotationMatrix()) * glm::vec4(0, 1, 0, 1);

	// We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
	return glm::vec3(upVector);
}

glm::vec3 Camera::GetRight()
{
	glm::vec4 rightVector = glm::inverse(GetRotationMatrix()) * glm::vec4(1, 0, 0, 1);

	// We are using a 4x4 matrix so our result is a vec4, but just cast it back to a vec3
	return glm::vec3(rightVector);
}

void Camera::Strafe(float speed)
{
	// Get our normalized right vector (The direction perpendicular to our view)
	glm::vec3 rightVector = GetRight();


}

void Camera::MoveCamera(float speed)
{
	_distance -= speed * 1;
}

glm::mat4 Camera::GetRotationMatrix()
{
	// Create an identity matrix
	return glm::inverse(_rotate);
}


void Camera::ptov(int x, int y, int width, int height, glm::vec3& v)
{
	glm::vec3 P = glm::vec3(1.0*x / width * 2 - 1.0,
		1.0*y / height * 2 - 1.0,
		0);
	P.y = -P.y;
	float OP_squared = P.x * P.x + P.y * P.y;

	if (OP_squared < 1 * 0.70710678118654752440)
	{
		P.z = sqrt(1 * 1 - OP_squared);
	}                            /* On hyperbola */
	else
	{
		double t = 1 / 1.41421356237309504880;
		P.z = t*t / sqrt(OP_squared);
	}

	v[0] = P[0];
	v[1] = P[1];
	v[2] = P[2];
}


void Camera::PressBtn(double x, double y, int width, int height, int but, double time)
{
	if (but == GLFW_MOUSE_BUTTON_LEFT)
	{
		lastTime = time;
		ptov(x, y, width, height, lastCurPos);
	}
	else if (but == GLFW_MOUSE_BUTTON_RIGHT)
	{
		angle = 0.0f;
	}
	else if (but == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		lastTime = time;
		ptov(x, y, width, height, lastCurPos);
	}
}
void Camera::ReleaseBtn(int but, double time)
{
	if (but == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (time != lastTime)
		{
			angle = 0.0f;
		}
	}
	else if (but == GLFW_MOUSE_BUTTON_RIGHT)
	{
	}
	else if (but == GLFW_MOUSE_BUTTON_MIDDLE)
	{
	}

}


void Camera::trackBall(int x, int y, int winWidth, int winHeight, double time)
{
	glm::vec3 curPos;
	ptov(x, y, winWidth, winHeight, curPos);


	if (curPos == lastCurPos) return;

	glm::mat4 rotation_matrix = glm::inverse(_rotate);

	glm::vec4 uv = rotation_matrix * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
	glm::vec4 sv = rotation_matrix * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
	glm::vec4 lv = rotation_matrix * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f);

	glm::vec3 p1 = glm::vec3(sv) * lastCurPos[0] + glm::vec3(uv) * lastCurPos[1] - glm::vec3(lv) * lastCurPos[2];
	glm::vec3 p2 = glm::vec3(sv) * curPos[0] + glm::vec3(uv) * curPos[1] - glm::vec3(lv) * curPos[2];

	glm::vec3 axi = glm::cross(p2, p1);
	axis[0] = axi[0];
	axis[1] = axi[1];
	axis[2] = axi[2];

	float len = sqrtf(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
	if (len > 0.0)
	{
		len = 1.0f / len;
		axis[0] *= len;
		axis[1] *= len;
		axis[2] *= len;
	}

	float t = glm::length((p2 - p1)) / (2.0 * 1);

	if (t > 1.0) t = 1.0;
	if (t < -1.0) t = -1.0;

	angle = glm::degrees(t);


	lastCurPos[0] = curPos[0];
	lastCurPos[1] = curPos[1];
	lastCurPos[2] = curPos[2];
}


void Camera::trackMotion(int btn, int x, int y, int winWidth, int winHeight, double time)
{

	if (btn == GLFW_MOUSE_BUTTON_LEFT)
	{
		trackBall(x, y, winWidth, winHeight, time);
	}
	else if (btn == GLFW_MOUSE_BUTTON_RIGHT)
	{

	}
	else if (btn == GLFW_MOUSE_BUTTON_MIDDLE)
	{
		glm::vec3 curPos;
		ptov(x, y, winWidth, winHeight, curPos);
		glm::mat4 rotation_matrix = glm::inverse(_rotate);

		float dx = curPos[0] - lastCurPos[0];
		float dy = curPos[1] - lastCurPos[1];

		panModel(-dx, -dy, 0.0f);

		lastCurPos[0] = curPos[0];
		lastCurPos[1] = curPos[1];
		lastCurPos[2] = curPos[2];

	}

	lastTime = time;



}


void Camera::updateData(void)
{

	glm::mat4 newR = glm::rotate(angle, glm::vec3(axis[0], axis[1], axis[2]));
	_rotate = newR * _rotate;

}


void Camera::panModel(const float dx, const float dy, const float dz)
{
	glm::mat4 rM = _rotate;

	glm::vec3 dv(dx, dy, dz);

	glm::vec4 t = _rotate * glm::vec4(dv, 1.0);

	_center.x += t.x;
	_center.y += t.y;
	_center.z += t.z;

}



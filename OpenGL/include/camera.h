//
//  camera.h
//  OpenGL
//
//  Created by xt on 15/8/9.
//  Copyright (c) 2015年 xt. All rights reserved.
//

#ifndef __OpenGL__camer__
#define __OpenGL__camer__

#include <stdio.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>					 
#include <glm/gtx/transform2.hpp>



#define PI 3.14159265358979323846264338327950288
#define GLM_FORCE_RADIANS

class Camera
{
public:
	Camera();

	// This sets and returns a perspective matrix that is build from the field of fiew, aspect ratio and near/far planes
	glm::mat4 SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);

	glm::mat4 GetProjectionMatrix() { return _projectionMatrix; }

	// This returns the current view matrix according to the camera's position and rotation
	glm::mat4 GetViewMatrix();

	// This calculates the current view vector from the rotation matrix (hard coded for now)
	glm::vec3 GetView();


	// This sets and gets the camera's movement speed
	void SetSpeed(double speed) { Speed = speed; }
	double GetSpeed() { return Speed; }

	// This sets the Position and the yaw and pitch rotations (in radians)
	void PositionCamera(float positionX, float positionY, float positionZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);

	// This will move the camera forward or backwards depending on the speed (negative for backwards)
	void MoveCamera(float speed);

	void SetRotationSpeed(double s) { RotationSpeed = s; }
	double GetRotationSpeed() { return  RotationSpeed; }

	void updateData(void);

	glm::mat4 GetRotationMatrix();
	glm::vec3 GetPosition();
	glm::vec3 GetUp();
	glm::vec3 GetRight();

	void Strafe(float speed);

	void PressBtn(double x, double y, int width, int height, int but, double time);
	void ReleaseBtn(int but, double time);
	void trackMotion(int but, int x, int y, int width, int height, double time);

protected:

	glm::mat4 _projectionMatrix;

	double _distance;									// The camera's position

	glm::mat4 _rotate;

	glm::vec3 _center;

	float RotationSpeed;

	float Speed;					// The camera's speed that is used with a time slice
									// The vertical rotation angle (in radians, x-axis
private:
	void ptov(int x, int y, int width, int height, glm::vec3& v);
	void panModel(const float dx, const float dy, const float dz);
	void trackBall(int x, int y, int winWidth, int winHeight, double time);
public:
	float axis[3];
	float angle;
	double MouseSpeed;

	glm::vec3 lastCurPos;
	double    lastTime;
};

#endif /* defined(__OpenGL__camer__) */

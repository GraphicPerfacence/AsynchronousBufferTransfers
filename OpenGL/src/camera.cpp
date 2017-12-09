    //
    //  camer.cpp
    //  OpenGL
    //
    //  Created by xt on 15/8/9.

    //  Copyright (c) 2015ƒÍ xt. All rights reserved.


#include "camera.h"
#include <GLFW/glfw3.h>


#if 0
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

void mouse_scroll_callback (GLFWwindow *window, double xoffse, double yoffse)
{
    camera->MoveCamera(yoffse);
}
#endif



Camera::Camera(){}

Camera::Camera(glm::vec3 position,glm::vec3 up,float yaw , float pitch):
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(3.0f),
    MouseSensitivity(0.02f)
{
    this->Position = position;
    this->WorldUp = up;
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(3.0f), MouseSensitivity(0.02f)
{
    this->Position = glm::vec3(posX, posY, posZ);
    this->WorldUp = glm::vec3(upX, upY, upZ);
    this->Yaw = yaw;
    this->Pitch = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::updateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    front.y = sin(glm::radians(this->Pitch));
    front.z = sin(glm::radians(this->Yaw)) * cos(glm::radians(this->Pitch));
    this->Front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
}

void Camera::ProcessMouseScroll(float yoffset)
{
    if (this->_fov >= 1.0f && this->_fov <= 45.0f)
        this->_fov -= yoffset;
    if (this->_fov <= 1.0f)
        this->_fov = 1.0f;
    if (this->_fov >= 45.0f)
        this->_fov = 45.0f;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    xoffset *= this->MouseSensitivity;
    yoffset *= this->MouseSensitivity;

    this->Yaw   += xoffset;
    this->Pitch += yoffset;

        // Make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
        {
        if (this->Pitch > 89.0f)
            this->Pitch = 89.0f;
        if (this->Pitch < -89.0f)
            this->Pitch = -89.0f;
        }

        // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
}
void Camera::ProcessKeyboard(Camera_Movement direction, GLfloat deltaTime)
{
    GLfloat velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
        this->Position += this->Front * velocity;
    if (direction == BACKWARD)
        this->Position -= this->Front * velocity;
    if (direction == LEFT)
        this->Position -= this->Right * velocity;
    if (direction == RIGHT)
        this->Position += this->Right * velocity;
}

glm::mat4 Camera::SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane)
{
    _fov = fov;
    _aspectRatio = aspectRatio;
    _nearP = nearPlane;
    _farP = farPlane;

    return glm::perspective(fov, aspectRatio, nearPlane, farPlane);
}

glm::mat4 Camera::GetProjectionMatrix()const
{
     return glm::perspective(_fov, _aspectRatio, _nearP, _farP);
}

void Camera::PositionCamera(float positionX, float positionY, float positionZ,
                            float centerX, float centerY, float centerZ,
                            float upX, float upY, float upZ)
                            {
                                this->Position = glm::vec3(positionX,positionY,positionZ);
                                this->WorldUp = glm::vec3(upX,upY,upZ);
                                glm::vec3 front = glm::vec3(centerX - positionX,centerY - positionY,centerZ - positionZ);

                                
                            }
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

    // Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods

 
class Camera
{

public:
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT
    };
    
    Camera();

    Camera(glm::vec3 position /*= glm::vec3(0.0f, 0.0f, 0.0f)*/,
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0, float pitch = 0.0f);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ,
            float yaw, float pitch);

    glm::mat4           GetViewMatrix();

    glm::mat4           SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);
    glm::mat4           GetProjectionMatrix()const;

    void                PositionCamera(float positionX, float positionY, float positionZ,
                                       float centerX, float centerY, float centerZ,
                                       float upX, float upY, float upZ);
                   
    void                ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void                ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
    void                ProcessMouseScroll(float yoffset);

private:
    void                updateCameraVectors();

private:
    glm::vec3               Position;
    glm::vec3               Front;
    glm::vec3               Up;
    glm::vec3               Right;
    glm::vec3               WorldUp;
        // Eular Angles
    float                   Yaw;
    float                   Pitch;
        // Camera options
    float                   MovementSpeed;
    float                   MouseSensitivity;

    float                   _aspectRatio;
    float                   _nearP;
    float                   _farP;
    float                   _fov;

    glm::mat4 ProjectionMatrix;
};

#endif
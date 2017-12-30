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

#include "defType.hpp"
 
class Camera
{

public:
    enum Camera_Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    enum Camera_Mouse_Button
    {
        LEFT_BUTTON,
        RIGHT_BUTTON,
        MIDDLE_BUTTON
    };
    enum Camera_Mouse_Action
    {
        PRESS,
        RELEASE,
        DRAG
    };

    enum Camera_Key_Action
    {
        KEY_PRESS,
        KEY_RELEASE,
        KEY_REPEAT
    };
    Camera();

    Camera(glm::vec3 position,
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = -90.0, float pitch = 0.0f);


    Matrixf             GetViewMatrix()const;
    glm::mat4           GetProjectionMatrix()const;

    glm::mat4           SetPerspective(float fov, float aspectRatio, float nearPlane, float farPlane);


    void                PositionCamera(float positionX, float positionY, float positionZ,
                                       float centerX, float centerY, float centerZ,
                                       float upX, float upY, float upZ);
                   
    void                ProcessKeyboard(Camera_Movement direction, Camera_Key_Action action, float deltaTime);
    
    void                ProcessMouseMovement(Camera_Mouse_Button button, Camera_Mouse_Action action,
                                                float xoffset, float yoffset,
                                                bool constrainPitch = true);

    void                ProcessMouseScroll(float yoffset);

    void                SetWindowSize(float width,float heigh);
private:
    void                updateCameraVectors();

    struct              EventAdapter
    {
        float           _mouseX;
        float           _mouseY;
    };

    float               getXnormalize(float x);
    float               getYnormalize(float y);

    void                addEventAdapter(float x,float y);

    void                rotateTrackball(const float px0,const float py0,const float px1,const float py1,float scale);
    void                trackball(V3f&axis,float&angle,float p1x,float p1y,float p2x,float p2y);
    float               projectToSphere(float r,float x,float y);

    bool                validAdapter()const;

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

    Quat<float>             m_rotaion;
    V3f                     m_center;
    float                   m_distance;

    float                   m_windowSize[2];

    glm::mat4 ProjectionMatrix;

    EventAdapter            m_adpter[2];
    
};

#endif
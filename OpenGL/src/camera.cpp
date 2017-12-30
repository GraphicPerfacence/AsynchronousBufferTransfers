    //
    //  camer.cpp
    //  OpenGL
    //
    //  Created by xt on 15/8/9.

    //  Copyright (c) 2015ƒÍ xt. All rights reserved.


#include "HelpF.h"
#include "camera.h"


Camera::Camera():
    MovementSpeed(3.0f)
{}

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

Matrixf Camera::GetViewMatrix()const
{

    Matrixf translate0;
    Matrixf translate1;

    translate0 = glm::translate(V3f(0.0,0.0,-m_distance));
    translate1 = glm::translate(-m_center);

    return translate0 * math::mfq(math::inverseQuat(m_rotaion)) * translate1;
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
    this->Front = glm::vec3(centerX - positionX,centerY - positionY,centerZ - positionZ);
    this->Up = glm::vec3(upX,upY,upZ);

    V3f lv(Front);
    V3f f(lv);
    math::normalizeVec3(f);
    V3f s(math::crossVec3(f,Up));
    math::normalizeVec3(s);
    V3f u(math::crossVec3(s , f));
    math::normalizeVec3(u);

    Matrixf rotateMat(
        s[0],u[0],-f[0],0.0f,
        s[1],u[1],-f[1],0.0f,
        s[2],u[2],-f[2],0.0f,
        0.0f,0.0f,0.0f,1.0
    );

    m_rotaion = math::inverseQuat(math::qfm(rotateMat));
    m_center = V3f(centerX,centerY,centerZ);
    m_distance = lv.length();

}
void Camera::SetWindowSize(float width,float heigh)
{
    _aspectRatio = width / heigh;
    m_windowSize[0] = width;
    m_windowSize[1] = heigh;

}
void Camera::ProcessMouseMovement(Camera_Mouse_Button button, Camera_Mouse_Action action,
                                  float xoffset, float yoffset, bool constrainPitch)
{
    addEventAdapter(xoffset,yoffset);

    if(button == LEFT_BUTTON)
    {
        if(action == DRAG)
        {

          if(validAdapter())
              rotateTrackball(getXnormalize(xoffset), getYnormalize(yoffset),
                            getXnormalize(m_adpter[1]._mouseX),
                            getYnormalize(m_adpter[1]._mouseY),
                             1.0);
        }
    }
    
}
void Camera::ProcessKeyboard(Camera_Movement direction, Camera_Key_Action action,float deltaTime)
{

    if(action == KEY_RELEASE)
    {
    float velocity = this->MovementSpeed * deltaTime;
    if (direction == FORWARD)
        m_distance -= velocity;
    if (direction == BACKWARD)
        m_distance += velocity;

    if (direction == LEFT || direction == RIGHT)
        {
        float d = 1.0;
        if(direction == LEFT)   d = -d;

        V3f dv(1.0,0.0,0.0);

        dv *= d;
        dv *= velocity;

        m_center += dv * m_rotaion;
        }

    }
}

float Camera::getXnormalize(float x)
{
    return  x / m_windowSize[0];
}
float  Camera::getYnormalize(float y)
{
    return  (m_windowSize[1] - y) / m_windowSize[1];
}

void   Camera::addEventAdapter(float x,float y)
{
    m_adpter[1] = m_adpter[0];
    m_adpter[0]._mouseX = x;
    m_adpter[0]._mouseY = y;

}

bool Camera::validAdapter()const
{
    if((m_adpter[0]._mouseX == m_adpter[1]._mouseX) &&
       (m_adpter[0]._mouseY == m_adpter[1]._mouseY)) return false;

       return  true;
}

void   Camera::rotateTrackball(const float px0,const float py0,const float px1,const float py1,float scale)
{
    V3f axis;
    float angle;

    trackball(axis, angle, px0 + (px1 - px0)*scale, py1 +  (py1 - py0)*scale, px0, py0);

    Quatf new_rotate = glm::angleAxis(angle,axis);

    m_rotaion = new_rotate * m_rotaion;


}
void  Camera::trackball(V3f&axis,float&angle,float p1x,float p1y,float p2x,float p2y)
{
        V3f uv = m_rotaion * V3f(0.0f,1.0f,0.0f);
        V3f sv = m_rotaion * V3f(1.0f,0.0f,0.0f);
        V3f lv = m_rotaion * V3f(0.0f,1.0f,-1.0f);

        V3f p1 = p1x * sv + p1y * uv - projectToSphere(0.7, p1x, p1y) * lv;
        V3f p2 = p2x * sv + p2y * uv - projectToSphere(0.7, p2x, p2y) * lv;

        axis = glm::cross(p2, p1);
        math::normalizeVec3(axis);

        float t = glm::length((p2 - p1)) / (2.0 * 0.7);


        if (t > 1.0) t = 1.0;
        if (t < -1.0) t = -1.0;
        angle = (asin(t));
}

float    Camera::projectToSphere(float r,float x,float y)
{
    float d,t,z;

    d = sqrt( x * x + y * y);

    if(d < r * 0.70710678118654752440)
    {
        z = sqrt(r * r - d * d);
    }
    else{
        t = r / 1.41421356237309504880;
        z = t * t / d;
    }

    return  z;
}
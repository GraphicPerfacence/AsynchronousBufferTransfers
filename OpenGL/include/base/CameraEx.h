    //
    //  Camera.h
    //  openGLTest
    //
    //  Created by xt on 17/12/11.
    //  Copyright © 2017年 xt. All rights reserved.
    //

#ifndef Camera_h
#define Camera_h

#include "math/const.h"
#include "math/HelpF.h"

template<class REAL = float>
class CameraEx
{
public:
    enum CameraBehavior
    {
    CAMERA_BEHAVIOR_FIRST_PERSON,
    CAMERA_BEHAVIOR_FLIGHT
    };
    enum Camera_Movement
    {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
    };

    CameraEx();
    ~CameraEx();

    void lookAt(const Vector3<REAL> &target);
    void lookAt(const Vector3<REAL> &eye, const Vector3<REAL> &target, const Vector3<REAL> &up);
    void move(REAL dx, REAL dy, REAL dz);
    void move(const Vector3<REAL> &direction, const Vector3<REAL> &amount);
    void perspective(float fovx, float aspect, float znear, float zfar);
    void rotate(float headingDegrees, float pitchDegrees, float rollDegrees);
    void updatePosition(const Vector3<REAL> &direction, float elapsedTimeSec);

        // Getter methods.

    const Vector3<REAL> &getAcceleration() const;
    inline CameraBehavior getBehavior() const {return  m_behavior;};
    const Vector3<REAL> &getCurrentVelocity() const;
    const Vector3<REAL> &getPosition() const;
    const glm::mat4 &getProjectionMatrix() const;
    const Vector3<REAL> &getVelocity() const;
    const Vector3<REAL> &getViewDirection() const;
    const glm::mat4 &getViewMatrix() const;
    const Vector3<REAL> &getXAxis() const;
    const Vector3<REAL> &getYAxis() const;
    const Vector3<REAL> &getZAxis() const;

        // Setter methods.

    void setAcceleration(float x, float y, float z);
    void setAcceleration(const Vector3<REAL> &acceleration);
    void setBehavior(CameraBehavior newBehavior);
    void setCurrentVelocity(float x, float y, float z);
    void setCurrentVelocity(const Vector3<REAL> &currentVelocity);
    void setPosition(float x, float y, float z);
    void setPosition(const Vector3<REAL> &position);
    void setVelocity(float x, float y, float z);
    void setVelocity(const Vector3<REAL> &velocity);

        //keyboard
    Vector3<REAL>   processKeyboard(Camera_Movement direction, float deltaTime);

private:
    void rotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees);
    void rotateFirstPerson(float headingDegrees, float pitchDegrees);
    void updateVelocity(const Vector3<REAL> &direction, float elapsedTimeSec);
    void updateViewMatrix(bool orthogonalizeAxes);

    static const float DEFAULT_FOVX;
    static const float DEFAULT_ZFAR;
    static const float DEFAULT_ZNEAR;
    static const Vector3<REAL> WORLD_XAXIS;
    static const Vector3<REAL> WORLD_YAXIS;
    static const Vector3<REAL> WORLD_ZAXIS;

    CameraBehavior m_behavior;
    float m_fovx;
    float m_znear;
    float m_zfar;
    float m_aspectRatio;
    float m_accumPitchDegrees;

    Vector3<REAL> m_eye;
    Vector3<REAL> m_xAxis;
    Vector3<REAL> m_yAxis;
    Vector3<REAL> m_zAxis;
    Vector3<REAL> m_viewDir;
    Vector3<REAL> m_acceleration;
    Vector3<REAL> m_currentVelocity;
    Vector3<REAL> m_velocity;

    glm::mat4 m_viewMatrix;
    glm::mat4 m_projMatrix;
};

    //-----------------------------------------------------------------------------

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getAcceleration() const
{ return m_acceleration; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getCurrentVelocity() const
{ return m_currentVelocity; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getPosition() const
{ return m_eye; }

template <class REAL>
inline const glm::mat4 &CameraEx<REAL>::getProjectionMatrix() const
{ return m_projMatrix; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getVelocity() const
{ return m_velocity; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getViewDirection() const
{ return m_viewDir; }

template <class REAL>
inline const glm::mat4 &CameraEx<REAL>::getViewMatrix() const
{ return m_viewMatrix; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getXAxis() const
{ return m_xAxis; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getYAxis() const
{ return m_yAxis; }

template <class REAL>
inline const Vector3<REAL> &CameraEx<REAL>::getZAxis() const
{ return m_zAxis; }

template <class REAL>
const float CameraEx<REAL>::DEFAULT_FOVX = 90.0f;
template <class REAL>
const float CameraEx<REAL>::DEFAULT_ZFAR = 1000.0f;
template <class REAL>
const float CameraEx<REAL>::DEFAULT_ZNEAR = 0.1f;
template <class REAL>
const Vector3<REAL> CameraEx<REAL>::WORLD_XAXIS(1.0f, 0.0f, 0.0f);
template <class REAL>
const Vector3<REAL> CameraEx<REAL>::WORLD_YAXIS(0.0f, 1.0f, 0.0f);
template <class REAL>
const Vector3<REAL> CameraEx<REAL>::WORLD_ZAXIS(0.0f, 0.0f, 1.0f);



template <class REAL>
CameraEx<REAL>::CameraEx()
{
    m_behavior = CAMERA_BEHAVIOR_FLIGHT;

    m_fovx = DEFAULT_FOVX;
    m_znear = DEFAULT_ZNEAR;
    m_zfar = DEFAULT_ZFAR;
    m_aspectRatio = 0.0f;

    m_accumPitchDegrees = 0.0f;


    m_eye = Vector3<REAL>(0.0f, 0.0f, 0.0f);
    m_xAxis = Vector3<REAL>(1.0f, 0.0f, 0.0f);
    m_yAxis = Vector3<REAL>(0.0f, 1.0f, 0.0f);
    m_zAxis = Vector3<REAL>(0.0f, 0.0f, 1.0f);
    m_viewDir = Vector3<REAL>(0.0f, 0.0f, -1.0f);

    m_acceleration = Vector3<REAL>(0.0f, 0.0f, 0.0f);
    m_currentVelocity = Vector3<REAL>(0.0f, 0.0f, 0.0f);
    m_velocity = Vector3<REAL>(0.0f, 0.0f, 0.0f);
}

template <class REAL>
CameraEx<REAL>::~CameraEx()
{
}

template <class REAL>
void CameraEx<REAL>::lookAt(const Vector3<REAL> &target)
{
    lookAt(m_eye, target, m_yAxis);
}

template <class REAL>
void CameraEx<REAL>::lookAt(const Vector3<REAL> &eye, const Vector3<REAL> &target,
                            const Vector3<REAL> &up)
{
    m_eye = eye;

    m_zAxis = eye - target;
    math::normalizeVec3(m_zAxis);

    m_viewDir = -m_zAxis;
    m_xAxis = glm::cross(up ,m_zAxis);
    math::normalizeVec3(m_xAxis);

    m_yAxis = glm::cross(m_zAxis , m_xAxis);
    math::normalizeVec3(m_yAxis);
    math::normalizeVec3(m_xAxis);

    m_viewMatrix[0][0] = m_xAxis.x;
    m_viewMatrix[1][0] = m_xAxis.y;
    m_viewMatrix[2][0] = m_xAxis.z;
    m_viewMatrix[3][0] = -math::dotVec3(m_xAxis ,  eye);

    m_viewMatrix[0][1] = m_yAxis.x;
    m_viewMatrix[1][1] = m_yAxis.y;
    m_viewMatrix[2][1] = m_yAxis.z;
    m_viewMatrix[3][1] = -math::dotVec3(m_yAxis ,  eye);

    m_viewMatrix[0][2] = m_zAxis.x;
    m_viewMatrix[1][2] = m_zAxis.y;
    m_viewMatrix[2][2] = m_zAxis.z;
    m_viewMatrix[3][2] = -math::dotVec3(m_zAxis ,  eye);

        // Extract the pitch angle from the view matrix.
    m_accumPitchDegrees = math::radinToDegree (-asinf(m_viewMatrix[1][2]));
}

template<class REAL>
void CameraEx<REAL>::move(REAL dx, REAL dy, REAL dz)
{
        // Moves the camera by dx world units to the left or right; dy
        // world units upwards or downwards; and dz world units forwards
        // or backwards.

    Vector3<REAL> eye = m_eye;
    Vector3<REAL> forwards;

    if (m_behavior == CAMERA_BEHAVIOR_FIRST_PERSON)
        {
            // Calculate the forwards direction. Can't just use the camera's local
            // z axis as doing so will cause the camera to move more slowly as the
            // camera's view approaches 90 degrees straight up and down.

        forwards = glm::cross(WORLD_YAXIS , m_xAxis);
        math::normalizeVec3(forwards);
        }
    else
        {
        forwards = m_viewDir;
        }

    eye += m_xAxis * dx;
    eye += WORLD_YAXIS * dy;
    eye += forwards * dz;

    setPosition(eye);
}

template<class REAL>
void CameraEx<REAL>::move(const Vector3<REAL> &direction, const Vector3<REAL> &amount)
{
        // Moves the camera by the specified amount of world units in the specified
        // direction in world space.

    m_eye.x += direction.x * amount.x;
    m_eye.y += direction.y * amount.y;
    m_eye.z += direction.z * amount.z;

    updateViewMatrix(false);
}

template<class REAL>
void CameraEx<REAL>::perspective(float fovx, float aspect, float znear, float zfar)
{
        // Construct a projection matrix based on the horizontal field of view
        // 'fovx' rather than the more traditional vertical field of view 'fovy'.

    float e = 1.0f / tanf(math::degreeToRadin(fovx) / 2.0f);
    float aspectInv = 1.0f / aspect;
    float fovy = 2.0f * atanf(aspectInv / e);
    float xScale = 1.0f / tanf(0.5f * fovy);
    float yScale = xScale / aspectInv;

    m_projMatrix[0][0] = xScale;
    m_projMatrix[0][1] = 0.0f;
    m_projMatrix[0][2] = 0.0f;
    m_projMatrix[0][3] = 0.0f;

    m_projMatrix[1][0] = 0.0f;
    m_projMatrix[1][1] = yScale;
    m_projMatrix[1][2] = 0.0f;
    m_projMatrix[1][3] = 0.0f;

    m_projMatrix[2][0] = 0.0f;
    m_projMatrix[2][1] = 0.0f;
    m_projMatrix[2][2] = (zfar + znear) / (znear - zfar);
    m_projMatrix[2][3] = -1.0f;

    m_projMatrix[3][0] = 0.0f;
    m_projMatrix[3][1] = 0.0f;
    m_projMatrix[3][2] = (2.0f * zfar * znear) / (znear - zfar);
    m_projMatrix[3][3] = 0.0f;

    m_fovx = fovx;
    m_aspectRatio = aspect;
    m_znear = znear;
    m_zfar = zfar;
}

template<class REAL>
void CameraEx<REAL>::rotate(float headingDegrees, float pitchDegrees, float rollDegrees)
{
        // Rotates the camera based on its current behavior.
        // Note that not all behaviors support rolling.

    switch (m_behavior)
    {
        case CAMERA_BEHAVIOR_FIRST_PERSON:
        rotateFirstPerson(headingDegrees, pitchDegrees);
        break;

        case CAMERA_BEHAVIOR_FLIGHT:
        rotateFlight(headingDegrees, pitchDegrees, rollDegrees);
        break;
    }

    updateViewMatrix(true);
}

template<class REAL>
void CameraEx<REAL>::rotateFlight(float headingDegrees, float pitchDegrees, float rollDegrees)
{


    glm::mat4 rotMtx;
        // Rotate camera's existing x and z axes about its existing y axis.
    if (headingDegrees != 0.0f)
        {
        rotMtx =  glm::rotate(headingDegrees,m_yAxis);
        glm::vec4 t = (rotMtx * glm::vec4(m_xAxis,0.0));
        m_xAxis.x = t.x;m_xAxis.y = t.y;m_xAxis.z = t.z;
        t = rotMtx * glm::vec4(m_zAxis,0.0);
        m_zAxis.x = t.x;m_zAxis.y = t.y;m_zAxis.z = t.z;
        }

        // Rotate camera's existing y and z axes about its existing x axis.
    if (pitchDegrees != 0.0f)
        {
        rotMtx =  glm::rotate(pitchDegrees,m_xAxis);

        glm::vec4 t = (rotMtx * glm::vec4(m_yAxis,0.0));
        m_yAxis.x = t.x;m_yAxis.y = t.y;m_yAxis.z = t.z;

        t = rotMtx * glm::vec4(m_zAxis,0.0);
        m_zAxis.x = t.x;m_zAxis.y = t.y;m_zAxis.z = t.z;

        }

        // Rotate camera's existing x and y axes about its existing z axis.
    if (rollDegrees != 0.0f)
        {
        rotMtx =  glm::rotate(rollDegrees,m_zAxis);

        glm::vec4 t = (rotMtx * glm::vec4(m_xAxis,0.0));
        m_xAxis.x = t.x;m_xAxis.y = t.y;m_xAxis.z = t.z;

        t = rotMtx * glm::vec4(m_yAxis,0.0);
        m_yAxis.x = t.x;m_yAxis.y = t.y;m_yAxis.z = t.z;

        }
}

template<class REAL>
void CameraEx<REAL>::rotateFirstPerson(float headingDegrees, float pitchDegrees)
{
    m_accumPitchDegrees += pitchDegrees;

    if (m_accumPitchDegrees > 90.0f)
        {
        pitchDegrees = 90.0f - (m_accumPitchDegrees - pitchDegrees);
        m_accumPitchDegrees = 90.0f;
        }

    if (m_accumPitchDegrees < -90.0f)
        {
        pitchDegrees = -90.0f - (m_accumPitchDegrees - pitchDegrees);
        m_accumPitchDegrees = -90.0f;
        }

    glm::mat4 rotMtx;

        // Rotate camera's existing x and z axes about the world y axis.
    if (headingDegrees != 0.0f)
        {

        rotMtx =  glm::rotate(headingDegrees,WORLD_YAXIS);

        glm::vec4 t = (rotMtx * glm::vec4(m_xAxis,0.0));
        m_xAxis.x = t.x;m_xAxis.y = t.y;m_xAxis.z = t.z;

        t = rotMtx * glm::vec4(m_zAxis,0.0);
        m_zAxis.x = t.x;m_zAxis.y = t.y;m_zAxis.z = t.z;

        }

        // Rotate camera's existing y and z axes about its existing x axis.
    if (pitchDegrees != 0.0f)
        {

        rotMtx =  glm::rotate(pitchDegrees,m_xAxis);
        glm::vec4 t = (rotMtx * glm::vec4(m_yAxis,0.0));
        m_yAxis.x = t.x;m_yAxis.y = t.y;m_yAxis.z = t.z;

        t = rotMtx * glm::vec4(m_zAxis,0.0);
        m_zAxis.x = t.x;m_zAxis.y = t.y;m_zAxis.z = t.z;


        }
}

template<class REAL>
void CameraEx<REAL>::setAcceleration(float x, float y, float z)
{
    m_acceleration = Vector3<REAL>(x, y, z);
}

template<class REAL>
void CameraEx<REAL>::setAcceleration(const Vector3<REAL> &acceleration)
{
    m_acceleration = acceleration;
}

template<class REAL>
void CameraEx<REAL>::setBehavior(CameraBehavior newBehavior)
{
    if (m_behavior == CAMERA_BEHAVIOR_FLIGHT && newBehavior == CAMERA_BEHAVIOR_FIRST_PERSON)
        {
            // Moving from flight-simulator mode to first-person.
            // Need to ignore camera roll, but retain existing pitch and heading.

        lookAt(m_eye, m_eye - m_zAxis, WORLD_YAXIS);
        }

    m_behavior = newBehavior;
}

template<class REAL>
void CameraEx<REAL>::setCurrentVelocity(float x, float y, float z)
{
    m_currentVelocity = Vector3<REAL>(x, y, z);
}

template<class REAL>
void CameraEx<REAL>::setCurrentVelocity(const Vector3<REAL> &currentVelocity)
{
    m_currentVelocity = currentVelocity;
}

template<class REAL>
void CameraEx<REAL>::setPosition(float x, float y, float z)
{
    m_eye = Vector3<REAL>(x, y, z);
    updateViewMatrix(false);
}

template<class REAL>
void CameraEx<REAL>::setPosition(const Vector3<REAL> &position)
{
    m_eye = position;
    updateViewMatrix(false);
}

template<class REAL>
void CameraEx<REAL>::setVelocity(float x, float y, float z)
{
    m_velocity = Vector3<REAL>(x, y, z);
}

template<class REAL>
void CameraEx<REAL>::setVelocity(const Vector3<REAL> &velocity)
{
    m_velocity = velocity;
}

template<class REAL>
void CameraEx<REAL>::updatePosition(const Vector3<REAL> &direction, float elapsedTimeSec)
{
        // Moves the camera using Newton's second law of motion. Unit mass is
        // assumed here to somewhat simplify the calculations. The direction vector
        // is in the range [-1,1].


    if (glm::length(m_currentVelocity) != 0.0f)
        {
            // Only move the camera if the velocity vector is not of zero length.
            // Doing this guards against the camera slowly creeping around due to
            // floating point rounding errors.

        Vector3<REAL> displacement = (m_currentVelocity * elapsedTimeSec) +
        (0.5f * m_acceleration * elapsedTimeSec * elapsedTimeSec);

            // Floating point rounding errors will slowly accumulate and cause the
            // camera to move along each axis. To prevent any unintended movement
            // the displacement vector is clamped to zero for each direction that
            // the camera isn't moving in. Note that the updateVelocity() method
            // will slowly decelerate the camera's velocity back to a stationary
            // state when the camera is no longer moving along that direction. To
            // account for this the camera's current velocity is also checked.

        if (direction.x == 0.0f && math::closeEnough(m_currentVelocity.x, 0.0f))
            displacement.x = 0.0f;

        if (direction.y == 0.0f && math::closeEnough(m_currentVelocity.y, 0.0f))
            displacement.y = 0.0f;

        if (direction.z == 0.0f && math::closeEnough(m_currentVelocity.z, 0.0f))
            displacement.z = 0.0f;

        move(displacement.x, displacement.y, displacement.z);
        }

        // Continuously update the camera's velocity vector even if the camera
        // hasn't moved during this call. When the camera is no longer being moved
        // the camera is decelerating back to its stationary state.

    updateVelocity(direction, elapsedTimeSec);
}

template<class REAL>
void CameraEx<REAL>::updateVelocity(const Vector3<REAL> &direction, float elapsedTimeSec)
{
        // Updates the camera's velocity based on the supplied movement direction
        // and the elapsed time (since this method was last called). The movement
        // direction is in the range [-1,1].

    if (direction.x != 0.0f)
        {
            // Camera is moving along the x axis.
            // Linearly accelerate up to the camera's max speed.

        m_currentVelocity.x += direction.x * m_acceleration.x * elapsedTimeSec;

        if (m_currentVelocity.x > m_velocity.x)
            m_currentVelocity.x = m_velocity.x;
        else if (m_currentVelocity.x < -m_velocity.x)
            m_currentVelocity.x = -m_velocity.x;
        }
    else
        {
            // Camera is no longer moving along the x axis.
            // Linearly decelerate back to stationary state.

        if (m_currentVelocity.x > 0.0f)
            {
            if ((m_currentVelocity.x -= m_acceleration.x * elapsedTimeSec) < 0.0f)
                m_currentVelocity.x = 0.0f;
            }
        else
            {
            if ((m_currentVelocity.x += m_acceleration.x * elapsedTimeSec) > 0.0f)
                m_currentVelocity.x = 0.0f;
            }
        }

    if (direction.y != 0.0f)
        {
            // Camera is moving along the y axis.
            // Linearly accelerate up to the camera's max speed.

        m_currentVelocity.y += direction.y * m_acceleration.y * elapsedTimeSec;

        if (m_currentVelocity.y > m_velocity.y)
            m_currentVelocity.y = m_velocity.y;
        else if (m_currentVelocity.y < -m_velocity.y)
            m_currentVelocity.y = -m_velocity.y;
        }
    else
        {
            // Camera is no longer moving along the y axis.
            // Linearly decelerate back to stationary state.

        if (m_currentVelocity.y > 0.0f)
            {
            if ((m_currentVelocity.y -= m_acceleration.y * elapsedTimeSec) < 0.0f)
                m_currentVelocity.y = 0.0f;
            }
        else
            {
            if ((m_currentVelocity.y += m_acceleration.y * elapsedTimeSec) > 0.0f)
                m_currentVelocity.y = 0.0f;
            }
        }

    if (direction.z != 0.0f)
        {
            // Camera is moving along the z axis.
            // Linearly accelerate up to the camera's max speed.

        m_currentVelocity.z += direction.z * m_acceleration.z * elapsedTimeSec;

        if (m_currentVelocity.z > m_velocity.z)
            m_currentVelocity.z = m_velocity.z;
        else if (m_currentVelocity.z < -m_velocity.z)
            m_currentVelocity.z = -m_velocity.z;
        }
    else
        {
            // Camera is no longer moving along the z axis.
            // Linearly decelerate back to stationary state.

        if (m_currentVelocity.z > 0.0f)
            {
            if ((m_currentVelocity.z -= m_acceleration.z * elapsedTimeSec) < 0.0f)
                m_currentVelocity.z = 0.0f;
            }
        else
            {
            if ((m_currentVelocity.z += m_acceleration.z * elapsedTimeSec) > 0.0f)
                m_currentVelocity.z = 0.0f;
            }
        }
}

template<class REAL>
void CameraEx<REAL>::updateViewMatrix(bool orthogonalizeAxes)
{
    if (orthogonalizeAxes)
        {
            // Regenerate the camera's local axes to orthogonalize them.

        math::normalizeVec3(m_zAxis);

        m_yAxis = glm::cross(m_zAxis , m_xAxis);
        math::normalizeVec3(m_yAxis);

        m_xAxis = glm::cross(m_yAxis ,m_zAxis);
        math::normalizeVec3(m_xAxis);

        m_viewDir = -m_zAxis;
        }

        // Reconstruct the view matrix.

    m_viewMatrix[0][0] = m_xAxis.x;
    m_viewMatrix[1][0] = m_xAxis.y;
    m_viewMatrix[2][0] = m_xAxis.z;
    m_viewMatrix[3][0] = -math::dotVec3(m_xAxis ,  m_eye);

    m_viewMatrix[0][1] = m_yAxis.x;
    m_viewMatrix[1][1] = m_yAxis.y;
    m_viewMatrix[2][1] = m_yAxis.z;
    m_viewMatrix[3][1] = -math::dotVec3(m_yAxis , m_eye);

    m_viewMatrix[0][2] = m_zAxis.x;
    m_viewMatrix[1][2] = m_zAxis.y;
    m_viewMatrix[2][2] = m_zAxis.z;
    m_viewMatrix[3][2] = -math::dotVec3(m_zAxis , m_eye);

    m_viewMatrix[0][3] = 0.0f;
    m_viewMatrix[1][3] = 0.0f;
    m_viewMatrix[2][3] = 0.0f;
    m_viewMatrix[3][3] = 1.0f;
}


template <class REAL>
Vector3<REAL>   CameraEx<REAL>::processKeyboard(Camera_Movement keyDirection, float deltaTime)
{
    static bool moveForwardsPressed = false;
    static bool moveBackwardsPressed = false;
    static bool moveRightPressed = false;
    static bool moveLeftPressed = false;
    static bool moveUpPressed = false;
    static bool moveDownPressed = false;

    Vector3<REAL> velocity = getCurrentVelocity();
    Vector3<REAL> direction;

    if (keyDirection == FORWARD)
        {
        if(!moveForwardsPressed)
            {
            moveForwardsPressed = true;
            setCurrentVelocity(velocity.x, velocity.y, 0.0);
            }
        direction.z += 1.0;
        }
    else
        {
        moveForwardsPressed = false;
        }

    if(keyDirection == BACKWARD)
        {
        if(!moveBackwardsPressed)
            {
            moveBackwardsPressed = true;
            setCurrentVelocity(velocity.x, velocity.y, 0.0);
            }
        direction.z -= 1.0;
        }
    else
        {
        moveBackwardsPressed = false;
        }

    if(keyDirection == LEFT)
        {
        if(!moveLeftPressed)
            {
            moveLeftPressed = true;
            setCurrentVelocity(0.0f, velocity.x, velocity.y);
            }
        direction.x -= 1.0;
        }
    else
        {
        moveLeftPressed = false;
        }
    
    if(keyDirection == RIGHT)
        {
        if(!moveRightPressed)
            {
            moveRightPressed = true;
            setCurrentVelocity(0.0, velocity.x, velocity.y);
            }
        direction.x += 1.0;
        }
    else
        {
        moveRightPressed = false;
        }



    if(keyDirection == UP)
        {
        if(!moveUpPressed)
            {
            moveUpPressed = true;
            setCurrentVelocity( velocity.x,0.0, velocity.y);
            }
        direction.y += 1.0;
        }
    else
        {
        moveUpPressed = false;
        }


    if(keyDirection == DOWN)
        {
        if(!moveDownPressed)
            {
            moveDownPressed = true;
            setCurrentVelocity( velocity.x,0.0, velocity.y);
            }
        direction.y -= 1.0;
        }
    else
        {
        moveDownPressed = false;
        }

    return  direction;
}





#include "../../src/base/CameraEx.tpp"
#endif

/* Camera_h */

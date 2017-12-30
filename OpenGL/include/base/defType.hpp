
#ifndef _OPENGL_DEF_TYPE_H
#define _OPENGL_DEF_TYPE_H

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/transform.hpp>

template <class REAL>
using  Vector3 = glm::tvec3<REAL, glm::highp> ;

template <class REAL>
using  Vector4 = glm::tvec4<REAL, glm::highp> ;

template <class REAL>
using Vector2 = glm::tvec2<REAL, glm::highp>;

template <class REAL>
using Matrix4 = glm::tmat4x4<REAL, glm::highp>;

template <class REAL>
using Quat = glm::tquat<REAL, glm::highp>;


template <class REAL>
using Matrix3 = glm::tmat3x3<REAL,glm::highp>;

typedef Vector3<float>   V3f;
typedef Vector3<double>  V3d;
typedef Vector2<float>   V2f;
typedef Vector2<double>  V2d;
typedef Matrix4<float>   Matrixf;
typedef Matrix4<double>  Matrixd;
typedef Quat<float >     Quatf;




#endif
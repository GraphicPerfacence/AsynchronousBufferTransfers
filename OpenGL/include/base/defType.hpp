
#ifndef _OPENGL_DEF_TYPE_H
#define _OPENGL_DEF_TYPE_H

#include <glm/glm.hpp>

template <class REAL>
using  Vector3 = glm::tvec3<REAL, glm::highp> ;

template <class REAL>
using  Vector4 = glm::tvec4<REAL, glm::highp> ;

template <class REAL>
using Vector2 = glm::tvec2<REAL, glm::highp>;

template <class REAL>
struct MatrixX :public glm::tmat4x4<REAL,glm::highp>
{
public:
    Vector3<REAL> mulHomogenPoint(const Vector3<REAL>&v)const
    {
        Vector4<REAL> tm =  this * Vector4<REAL>(v,1.0);
        return Vector3<REAL>(tm.x/tm.w, tm.y/tm.w, tm.z/tm.w);

    }
};

template <class REAL>
using Matrix4 = MatrixX<REAL>;

typedef Vector3<float> V3f;
typedef Vector3<double> V3d;
#endif
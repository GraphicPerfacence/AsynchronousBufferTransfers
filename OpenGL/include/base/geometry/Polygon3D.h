
#ifndef _OPENGL_Polygon3DH
#define _OPENGL_Polygon3DH
    //---------------------------------------------------------------------------
#include <vector>
#include "../defType.hpp"
#include "Plane.h"
    //------------------

    //vector of 3d points
template<class REAL>
class VecVector3 : public std::vector<Vector3<REAL> >
{
    typedef Vector3<REAL> V3;
    typedef Matrix4<REAL> M4;
    typedef Plane<REAL> Plane;

    void                    Transform(VecVector3& polyOut, const VecVector3& polyIn, const M4& xForm)
    {
        polyOut.resize(polyIn.size());
        for(unsigned i = 0; i < polyIn.size(); i++) {
            polyOut[i] = xForm.mulHomogenPoint(polyIn[i]);
        }
    }
    typedef typename std::vector<Vector3<REAL>>::iterator iterator;


public:
    VecVector3() { }

    VecVector3(const VecVector3& vec, const M4& xForm)
    {
        transform(*this,vec,xForm);
    }

    VecVector3& operator*=(const M4& xForm)
    {
        for(iterator i = this->begin(); i != this->end(); i++) {
            *i = xForm.mulHomogenPoint(*i);
        }
        return *this;
    }

    const int               FindAlikePointID(const V3& p) {
        for(unsigned i = 0; i < this->size(); i++) {
            if(this->operator[](i).alike(p,(REAL)0.001)) {
                return i;
            }
        }
        return -1;
    }

        //the polygon is clipped to the part behind the plane (positive half-space is clip-space)
    void                    ClipAsPolygonByPlane(const Plane& A, VecVector3& polyOut, VecVector3& interPts) const {
        if(this->size() < 3) {
            return;
        }
        std::vector<bool> outside(this->size());
            //for each point mark the points in front of the plane
            //the points that will be clipped away
        for(unsigned i = 0; i < this->size(); i++) {
            outside[i] = A.PlaneBehindPoint(this->operator[](i));
        }
        for(unsigned i = 0; i < this->size(); i++) {
                //id of the second point of the edge
            const unsigned idNext = (i+1) % this->size();
                //both outside -> save none
            if(outside[i] && outside[idNext]) {
                continue;
            }
                //outside to inside -> calc intersection save intersection and save i+1
            if(outside[i]) {
                V3 inter;
                if(A.IntersectionWithEdge(inter,this->operator[](i),this->operator[](idNext))) {
                    polyOut.push_back(inter);
                    interPts.push_back(inter);
                }
                polyOut.push_back(this->operator[](idNext));
                continue;
            }
                //inside to outside -> calc intersection save intersection
            if(outside[idNext]) {
                V3 inter;
                if(A.IntersectionWithEdge(inter,this->operator[](i),this->operator[](idNext))) {
                    polyOut.push_back(inter);
                    interPts.push_back(inter);
                }
                continue;
            }
                //both inside -> save point i+1
            polyOut.push_back(this->operator[](idNext));
        }
    }

};


template<class REAL>
struct Polygon3D
{
    typedef Vector3<REAL> V3;
    typedef VecVector3<REAL> VecVec3;

    VecVec3 points;
    const V3                GetNormal() const
    {
        if(points.size() < 3)
        {
            return V3::ZERO();
        }
        const V3 a = points[1]-points[0];
        const V3 b = points[2]-points[1];
        V3 n;
        n.unitCross(a,b);
        return n;

    }


};

#endif


#ifndef _OPENGL_AABox_H
#define _OPENGL_AABox_H

#include "GemoetoryException.hpp"

#include "Plane.h"
#include "Line.h"

#include "../../math/HelpF.h"

    //Axis-Aligned Bounding Box defined through the two extreme points
template<class REAL = float>

struct AABox
{
    typedef Vector3<REAL> V3;

protected:
    typedef Plane<REAL> Plane;
    typedef AABox<REAL> B;
    V3 min, max;


    inline void CorrectMinMax()
    {
        for(unsigned i = 0; i < 3; i++)
        {
            if(min[i] > max[i])
            {
                std::swap(min[i],max[i]);
            }
        }
    }

    enum Axe { X = 0, Y = 1, Z = 2 };

    inline void ExpandToContain(const unsigned axe, const REAL& value)
    {
        if(value > max[axe])
        {
            max[axe] = value;
        }
        else
        {
            if(value < min[axe])
            {
                min[axe] = value;
            }
        }
    }

public:

    AABox(const AABox& box): min(box.getMin()), max(box.getMax()) { }
    AABox(const V3& vA, const V3& vB): min(vA), max(vB) { CorrectMinMax(); }

    template<class T> AABox(const T& points)
    {
        if(0 == points.size())
        {
            throw GeometryException("empty point list in AABox constructor");
        }

        min = (max = points[0]); //attention not with AABox::ZERO

        for(unsigned i = 1; i < points.size(); i++)
        {
            ExpandToContain(points[i]);
        }
    }

    template<class T> AABox(const T& points, const Matrix4<REAL>& mtxTransform)
    {
        if(0 == points.size())
        {
            throw GeometryException("empty point list in AABox constructor");
        }

        min = (max = mtxTransform.mulHomogenPoint(points[0])); //attention not with AABox::ZERO

        for(unsigned i = 1; i < points.size(); i++)
        {
            ExpandToContain(mtxTransform.mulHomogenPoint(points[i]));
        }
    }

    inline const V3&                        GetMin() const { return min; }
    inline const V3&                        GetMax() const { return max; }
    inline V3                               GetCenter() const {	return GetMin()+GetExtents(); }
    inline V3                               GetExtents() const { return (GetMax()-GetMin())*0.5; }
    inline REAL                             Volume() const { return (GetMax()-GetMin()).abs().product(); }

    inline void                             ExpandToContain(const V3& v)
    {
        for(unsigned j = 0; j < v.size(); j++)
        {
            expandToContain(j,v[j]);
        }
    }

    inline AABox& operator                  +=(const AABox& a)
    {
        ExpandToContain(a.GetMin());
        ExpandToContain(a.GetMax());
        return *this;
    }
    AABox& operator                         =(const AABox& box)
    {
            min = box.getMin();
            max = box.getMax();
            return *  this;
    }

    inline AABox operator                   +(const AABox& a) const
    {
        B result(*this);
        result.ExpandToContain(a.GetMin());
        result.ExpandToContain(a.GetMax());
        return result;
    }

    template<class T> AABox<T>              Convert2() const
    {
        return AABox<T>(GetMin(),GetMax());
    }

        //calculates the 8 corner points of the AABox
    template<class T> void                  ComputeVerticesLeftHanded(T& v) const
    {
        if(8 > v.size())
        {
            throw GeometryException("AABox::computeVerticesLeftHanded with structure smaller 8 Vectors called");
        }

        const V3& m = GetMin();
        const V3& M = GetMax();
            //generate 8 corners of the bbox
        v[0] = V3(m[0],m[1],m[2]); //     7+------+6
        v[1] = V3(M[0],m[1],m[2]); //     /|     /|
        v[2] = V3(M[0],M[1],m[2]); //    / |    / |
        v[3] = V3(m[0],M[1],m[2]); //   / 4+---/--+5
        v[4] = V3(m[0],m[1],M[2]); // 3+------+2 /    y   z
        v[5] = V3(M[0],m[1],M[2]); //  | /    | /     |  /
        v[6] = V3(M[0],M[1],M[2]); //  |/     |/      |/
        v[7] = V3(m[0],M[1],M[2]); // 0+------+1      *---x
    }

        //calculates the 8 corner points of the AABox
    template<class T> void                  ComputeVerticesRightHanded(T& v) const
    {
        if(8 > v.size())
        {
            throw GeometryException("AABox::computeVerticesLeftHanded with structure smaller 8 Vectors called");
        }
        const V3& m = GetMin();
        const V3& M = GetMax();
            //generate 8 corners of the bbox
        v[0] = V3(m[0],m[1],M[2]); //     7+------+6
        v[1] = V3(M[0],m[1],M[2]); //     /|     /|
        v[2] = V3(M[0],M[1],M[2]); //    / |    / |
        v[3] = V3(m[0],M[1],M[2]); //   / 4+---/--+5
        v[4] = V3(m[0],m[1],m[2]); // 3+------+2 /    y  -z
        v[5] = V3(M[0],m[1],m[2]); //  | /    | /     |  /
        v[6] = V3(M[0],M[1],m[2]); //  |/     |/      |/
        v[7] = V3(m[0],M[1],m[2]); // 0+------+1      *---x
    }

        //calculates the 6 planes of the given AABox
    template<class T> void                  CalcAABoxPlanes(T& planes) const
    {
        const V3& min = GetMin();
        const V3& max = GetMax();

        if(6 > planes.size())
        {
            throw GeometryException("AABox::calcAABoxPlanes structure has no place for 6 planes");
        }
            //bottom plane
        planes[0] = Plane(0,-1,0,std::abs(min[1]));
            //top plane
        planes[1] = Plane(0,1,0,std::abs(max[1]));
            //left plane
        planes[2] = Plane(-1,0,0,std::abs(min[0]));
            //right plane
        planes[3] = Plane(1,0,0,std::abs(max[0]));
            //back plane
        planes[4] = Plane(0,0,-1,std::abs(min[2]));
            //front plane
        planes[5] = Plane(0,0,1,std::abs(max[2]));
    }

    bool                                    IntersectWithLine(V3& v, const Line<REAL>& l) const
    {
        const V3& p = l.p;
        const V3& dir = l.dir;
        const V3& min = GetMin();
        const V3& max = GetMax();
        REAL t1 = 0.0;
        REAL t2 = Const<REAL>::infinity();
        bool intersect =
        clipTest(-dir[2],p[2]-min[2],t1,t2) && clipTest(dir[2],max[2]-p[2],t1,t2) &&
        clipTest(-dir[1],p[1]-min[1],t1,t2) && clipTest(dir[1],max[1]-p[1],t1,t2) &&
        clipTest(-dir[0],p[0]-min[0],t1,t2) && clipTest(dir[0],max[0]-p[0],t1,t2);

        if(!intersect)
        {
            return false;
        }

        intersect = false;
        if(0 <= t1)
        {
            v = p;
            v += t1*dir;
            intersect = true;
        }

        if(0 <= t2)
        {
            v = p;
            v += t2*dir;
            intersect = true;
        }

        return intersect;
    }

    const PlaneSide                             GetPlaneSide(const Plane& A) const
    {
        const V3& n = A.GetN();
        const V3 min = GetMin();
        const V3 max = GetMax();

        V3 vMin, vMax;
            //extend: the for could be cached in table for speedup, but the 3 if remain
        for(unsigned i = 0; i < V3::size(); i++)
        {
            if(n[i] >= 0.0)
            {
                vMin[i] = min[i];
                vMax[i] = max[i];
            }
            else
            {
                vMin[i] = max[i];
                vMax[i] = min[i];
            }
        }

        if(A.Distance(vMin) > 0.0)
        {
            return BEFORE;
        }

        if(A.Distance(vMax) < 0.0)
        {
            return BEHIND;
        }
        return CROSS;
    }

    REAL                                            SquaredDistance(const V3& p) const
    {
        const V3 e(GetExtents());

            // compute coordinates of point in box coordinate system
        V3 s(p-GetCenter());
        for(unsigned i = 0; i < V3::size(); i++)
        {
            if(s[i] <= -e[i])
            {
                s[i] += e[i];
            }

            else
            {
                if(s[i] < e[i])
                {
                    s[i] = REAL(0.0);
                }
                else
                {
                    s[i] -= e[i];
                }
            }
        }
        return s.dot(s);
    }

    inline REAL                                     Distance(const V3& p) const
                                                    { return std::sqrt(SquaredDistance(p)); }

    inline AABox                                    Copy() const { return AABox(*this); }

    inline AABox&                                   Scale(const REAL& factor)
    {
        min *= factor;
        max *= factor;
        return *this;
    }

    inline AABox&                                   ScaleCenter(const REAL& factor)
    {
        V3 extents = GetExtents();
        const V3 center = GetMin()+extents;
        extents *= factor;
        min = center-extents;
        max = center+extents;
        return *this;
    }

    inline AABox&                                   Translate(const V3& translation)
    {
        min += translation;
        max += translation;
        return *this;
    }
        //AABox
};


#endif

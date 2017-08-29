
#ifndef _OPENGL_FrustumH
#define _OPENGL_FrustumH
    //---------------------------------------------------------------------------


#include "Plane.h"
#include "AABB.hpp"

#include <bitset>
#include <vector>



template<class REAL = float>
class Frustum
{
protected:
    typedef Plane<REAL> Plane;
    typedef AABox<REAL> AABox;
    typedef Vector3<REAL> V3;
public:
    typedef std::vector<Plane> VecPlane;
    typedef std::bitset<32> ActivePlanes;
    typedef Matrix4<REAL> Matrix4;

protected:
    VecPlane vecPlane;
    ActivePlanes activePlanes;

public:
    Frustum() { activePlanes.reset(); }

    void                            Clear()
    {
        vecPlane.clear();
        activePlanes.reset();
    }

    bool                            IsActive(unsigned int id) const
    {
        if(id > vecPlane.size())
        {
            throw GeometryException("Frustum::isActive: invalid plane");
        }
        return activePlanes[id];
    }

    unsigned                        ActivePlaneCount() const
    {
        return activePlanes.count();
    }

    void                            AddClipPlane(const Plane& p)
    {
        if(vecPlane.size() < activePlanes.size())
        {
            vecPlane.push_back(p);
            activePlanes[vecPlane.size()-1] = true;
        }
        else
        {
            throw GeometryException("Frustum: to many ClipPlanes");
        }
    }

    const Plane&                    GetPlaneUnChecked(unsigned int id) const { return vecPlane[id]; }

    const Plane&                    GetPlane(unsigned int id) const
    {
        if(id < vecPlane.size())
        {
            return GetPlaneUnChecked(id);
        }
        else
        {
            throw GeometryException("Frustum::getPlane: invalid plane");
        }
    }

    const VecPlane&                 GetVecPlanes() const { return vecPlane; }

    const ActivePlanes&             GetActivePlanes() const { return activePlanes; }

    ActivePlanes&                   GetActivePlanes() { return activePlanes; }

    bool                            Contains(const V3& p) const
    {
        for(uint i = 0; i < vecPlane.size(); i++)
        {
            if(activePlanes[i] && vecPlane[i].inFront(p))
            {
                return false;
            }
        }
        return true;
    }

    bool                            Contains(const V3& p, const ActivePlanes& ap) const
    {
        unsigned size = std::min(ap.size(),vecPlane.size());

        for(unsigned i = 0; i < size; i++)
        {
            if(vecPlane[i].inFront(p)) {
                return false;
            }
        }
        return true;
    }

    bool                            Inside(const AABox& box, const ActivePlanes& ap) const
    {
        std::vector<V3> p;

        box.ComputeVerticesRightHanded(p);
        for(unsigned i = 0; i < 8; i++)
        {
            if(!Contains(p[i],ap))
            {
                return false;
            }
        }
        return true;
    }

        //bool visible(const OBox&) const;
    bool                               Visible(const AABox& box) const
    {
        if(activePlanes.none())
        {
            return true;
        }

        ActivePlanes help = activePlanes;
        for(unsigned i = 0; help.any(); i++, help >>= 1)
        {
                // i < vecPlane.size test is superflue if the active planes are valid(only contains 1s where planes are existent)
            if(help[0])
            {
                if(BEHIND == box.GetPlaneSide(vecPlane[i]))
                {
                    return false;
                }
            }
        }
        return true;
    }

        //returns true if the box can be culled
        //updates activePlanes if the AABox lies in front of a plane and therefor
        //child boxes don't need to check this plane
    bool                                    Cull(const AABox& box)
    {
        if(activePlanes.none())
        {
            return false;
        }
        ActivePlanes help = activePlanes;
        for(uint i = 0; /*i < vecPlane.size() &&*/ help.any(); i++, help >>= 1)
        {
                // vecPlane.size test is superflue if the active planes only contains 1s where planes are existent
            if(help[0])
            {
                const PlaneSide ps = box.GetPlaneSide(vecPlane[i]);
                if(ps == BEHIND)
                {
                    return true;
                }
                if(ps == BEFORE)
                {
                    activePlanes[i] = false;
                }
            }
        }
        return false;
    }
};


#endif

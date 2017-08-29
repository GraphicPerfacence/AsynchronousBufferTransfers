
#ifndef OPENGL_Object_DMS_H
#define OPENGL_Object_DMS_H
//---------------------------------------------------------------------------


#include "Plane.h"
#include "AABB.hpp"
#include "Frustum.h"
#include "Polygon3D.h"

#include <vector>
#include <algorithm>

template<class REAL>
struct Object
{
	typedef Vector3<REAL>           V3;
	typedef Matrix4<REAL>           M4;
	typedef Line<REAL>              Line;
	typedef Plane<REAL>             Plane;
	typedef AABox<REAL>             AABox;
	typedef std::vector<V3>         Vector3x8;
	typedef VecVector3<REAL>        VecVec3;
	typedef Polygon3D<REAL>         Polygon;


    typedef typename std::vector<Polygon3D<REAL>>::iterator iterator;

    typedef std::vector<Polygon> VecPolygon;

    VecPolygon polygon;

	void                            CreateFromFrustPoints(const Vector3x8& p)
    {
		//reserve space
		polygon.resize(6);
		for(unsigned i = 0; i < 6; i++)
        {
			polygon[i].points.resize(4);
		}
		//near poly ccw
		for(unsigned i = 0; i < 4; i++)
        {
			polygon[0].points[i] = p[i];
		}
		//far poly ccw
		for(unsigned i = 4; i < 8; i++)
        {
			polygon[1].points[i-4] = p[11-i];
		}
		//left poly ccw
		polygon[2].points[0] = p[0];
		polygon[2].points[1] = p[3];
		polygon[2].points[2] = p[7];
		polygon[2].points[3] = p[4];
		//right poly ccw
		polygon[3].points[0] = p[1];
		polygon[3].points[1] = p[5];
		polygon[3].points[2] = p[6];
		polygon[3].points[3] = p[2];
		//bottom poly ccw
		polygon[4].points[0] = p[4];
		polygon[4].points[1] = p[5];
		polygon[4].points[2] = p[1];
		polygon[4].points[3] = p[0];
		//top poly ccw
		polygon[5].points[0] = p[6];
		polygon[5].points[1] = p[7];
		polygon[5].points[2] = p[3];
		polygon[5].points[3] = p[2];
	}

	//calculates the six polygons defining a frustum
	void                            CreateFromFrustMatrix(const M4& invProjView)
    {
		Vector3x8 pts;
		CalcFrustumWorldCoord(pts,invProjView);
		CreateFromFrustPoints(pts);
	}

	//with coordinate system change, like in OpenGL
	void                            CreateFromFrustMatrixGL(const M4& invProjViewGL)
    {
		Vector3x8 pts;
		CalcFrustumWorldCoordGL(pts,invProjViewGL);
		CreateFromFrustPoints(pts);
	}

	int                             FindSamePointAndSwapWithLast(const V3& p)
    {
		if(1 > polygon.size())
        {
			return -1;
		}
		for(unsigned i = polygon.size(); i > 0; i--)
        {
			VecVec3& poly = polygon[i-1].points;
			if(2 == poly.size())
            {
				const int nr = poly.FindAlikePointID(p);
				if(0 <= nr)
                {
					//swap with last
					poly.swap(polygon.back().points);
					return nr;
				}
			}
		}
		return -1;
	}

	void                            MakeClosingPolygon(VecVec3& polyOut, const V3& n)
    {
		//todo: compact inter: remove all polys with size != 2
		for(unsigned i = polygon.size(); 0 < i; i--)
        {
			if(2 == polygon[i-1].points.size())
            {
				break;
			}
		}
		polygon.resize(i);
		//you need at least 3 sides for a polygon
		if(3 > polygon.size())
        {
			return;
		}
		//we have line segments in each poly of inter 
		//take last linesegment as first and second point
		const VecVec3& polyIn = polygon.back().points;
		polyOut.push_back(polyIn[0]);
		polyOut.push_back(polyIn[1]);
		//remove last poly from inter, because it is already saved
		polygon.pop_back();

		//search edges that can be stitched together (have a point in common)
		//iterate over the intersectionEdges until their is no line segment left
		while(0 < polygon.size())
        {
			//pointer on last point to compare
			const V3 &lastPt = polyOut[polyOut.size()-1];
			//find same point in inter to continue polygon
			const int nr = FindSamePointAndSwapWithLast(lastPt);
			if(0 <= nr)
            {
				//last edge
				const VecVec3& polyIn = polygon.back().points;
				//get the other point in this polygon and save into polyOut
				polyOut.push_back(polyIn[(nr+1)%2]);
			}
			//remove last poly from inter, because it is already saved or degenerated
			polygon.pop_back();
		}
		//last point can be deleted, because he is the same as the first (closes polygon)
		polyOut.resize(polyOut.size()-1);
		//check for correct winding
		Plane planePoly(polyOut[0],polyOut[1],polyOut[2]);
		if(!n.alike(planePoly.getN(),REAL(0.01)))
        {
			//normal of polygon points in different direction than normal of clipping plane
			//-> reverse winding
			std::reverse(polyOut.begin(),polyOut.end());
		}
	}

	//the given object is clipped by the given plane; the object is assumed closed
	//and is closed after the clipping 
	//the part of the object in front of the plane is clipped (positive half-space is clip-space)
	void                            GetclippedByPositiveHalfSpaceOfPlane(const Plane& A, Object& objOut) const
    {
		Object intersectionEdges;
		Object objIn(*this);
		if(0 == polygon.size())
			return;
		objOut.polygon.clear();

		for(unsigned i = 0; i < objIn.polygon.size(); i++)
        {
			const unsigned size = objOut.polygon.size();
			objOut.polygon.resize(size+1);
			intersectionEdges.polygon.resize(size+1);
			objIn.polygon[i].points.ClipAsPolygonByPlane(A,objOut.polygon[size].points,intersectionEdges.polygon[size].points);
			//if whole poly was clipped away -> delete empty poly
			if(0 == objOut.polygon[size].points.size())
            {
				objOut.polygon.resize(size);
				intersectionEdges.polygon.resize(size);
			}
		}
		if(intersectionEdges.polygon.size() > 0)
        { //not everything was clipped away
			//make place for one additional polygon in objOut to close it
			objOut.polygon.resize(objOut.polygon.size()+1);
			//add a polygon of all intersection edges with plane to close the object
			intersectionEdges.MakeClosingPolygon(objOut.polygon.back().points,A.getN());
		}
	}

	//the given object is clipped by the given AABox; 
	//the object is assumed closed and is closed after the clipping
	void                            ClipByAABox(const AABox& box)
    {
		std::vector<Plane> planes;
        planes.resize(6);

		box.CalcAABoxPlanes(planes);

        for(unsigned i = 0; i < planes.size(); i++)
        {
			GetclippedByPositiveHalfSpaceOfPlane(planes[i],*this);
		}
	}

	//the given object is clipped by the given Frustum (with inverted planes);
	//the object is assumed closed and is closed after the clipping
	void                            ClipByFrustum(const Frustum<REAL>& frust)
    {
		for(unsigned i = 0; i < frust.activePlaneCount(); i++)
        {
			const Plane& p = frust.getPlane(i);
			const Plane inv = p.getInverted();
			GetclippedByPositiveHalfSpaceOfPlane(inv,*this);
		}
	}

	//the given object is clipped by the Frustum calculated from the projCam matrix given;
	//the object is assumed closed and is closed after the clipping
	void                            ClipByFrustum(const M4& projectionCamera)
    {
		Frustum<REAL> frust;
		aAdProjCamPlanes(frust,projectionCamera);
		ClipByFrustum(frust);
	}

	//the given object is clipped by the near plane of the Frustum calculated from the projCam matrix given;
	//the object is assumed closed and is closed after the clipping
	void                            ClipByNearPlane(const M4& projectionCamera)
    {
		Frustum<REAL> frust;
		AddProjCamPlanes(frust,projectionCamera);
		frust.GetActivePlanes().reset();
		frust.GetActivePlanes().set(0);
		ClipByFrustum(frust);
	}

	//the given object is clipped by the Frustum calculated from the projCam matrix given;
	//the projcam matrix includes a coordinate system change from right to left handed (OpenGL style)
	//the object is assumed closed and is closed after the clipping
	void                            ClipByFrustumGL(const M4& glProjectionCamera)
    {
		Frustum<REAL> frust;
		AddGlProjCamPlanes(frust,glProjectionCamera);
		ClipByFrustum(frust);
	}

	//extrudes the object into -lightDir and clippes by the AABox the defining points are returned
	void                            IncludeObjectLightVolume(VecVec3& points, const V3& lightDir, const AABox& sceneAABox) const
    {
		V3 ld(-lightDir[0],-lightDir[1],-lightDir[2]);
		calcPoints(points,*this);
		const unsigned size = points.size();
		//for each point add the point on the ray in -lightDir
		//intersected with the sceneAABox
		for(unsigned i = 0; i < size; i++)
        {
			V3 pt;
			if(sceneAABox.IntersectWithLine(pt,Line(points[i],ld)) )
            {
				points.push_back(pt);
			}
		}
	}


	void                            RemoveVisiblePolygons(const V3& p)
    {
		//delete all polygons that the point can see ->
		for(iterator i = polygon.begin(); i != polygon.end();)
        {
			const Polygon& poly = *i;
			if(poly.points.size() < 3)
            { // delete malformed polygons
				i = polygon.erase(i);
				continue;
			}
			//determine the polygon plane and look if the point is on the positive side
			Plane pl(poly.points[0],poly.points[1],poly.points[2]);
			if(BEFORE == pl.GetPlaneSide(p))
            { // plane is visible for point
				//delete poly
				i = polygon.erase(i);
				continue;
			}
			i++;
		}
	}
};

 
#endif

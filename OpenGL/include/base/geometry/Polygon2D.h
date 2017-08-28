//Copyright and Disclaimer:
//This code is copyright Daniel Scherzer, 2005.
#ifndef _OPENGL_Polygon2D_H
#define _OPENGL_Polygon2D_H
//---------------------------------------------------------------------------

#include "../defType.hpp"
#include "GemoetoryException.hpp"
#include <vector>
//---------------------------------------------------------------------------


template<class REAL = float>
class Polygon2D
{
protected:
	typedef Vector2<REAL> V2;
public:
	typedef std::vector<V2> VecPoint;
	VecPoint points;

	void                    Check() const
    {
		if(points.size() < 3)
         {
			throw GeometryException("Polygon2D with less than 3 points");
		}
	}

	bool                    Inside(const V2& p)
    {
		return false;
	}
};


#endif

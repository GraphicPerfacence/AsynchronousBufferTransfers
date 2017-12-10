
#ifndef _OPENGL_LINE2_H
#define _OPENGL_LINE2_H

#include "defType.hpp"

template<class REAL>
struct Line2D
{
	typedef Vector2<REAL> V2;

	V2 p;
	V2 dir;

    Line2D() { /* no initialization -> performance */ }
	Line2D(const V2& vP, const V2& vDirection): p(vP), dir(vDirection) { }

	bool operator               ==(const Line2D& l) const { return p == l.p && dir == l.dir; }
	bool operator               != (const Line2D& l) const { return !operator==(l); }


	V2                          GetPoint(const REAL& t) const { return p+dir*t; }
	V2                          GetLeftN() const { return V2(-dir.y(),dir.x()); }
	V2                          GetRightN() const { return V2(dir.y(),-dir.x()); }

	bool                        LeftofLine(const V2& point) const
    {
		const V2& leftN = GetLeftN();
		const V2 vec(point-p);
		if(vec.dot(leftN) > REAL(0.0))
        {
			return true;
		}
		return false;
	}

	const static Line2D ZERO;
};


 
#endif
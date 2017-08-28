
#ifndef _OPENGL_LINE_H
#define _OPENGL_LINE_H

#include "../defType.hpp"

template<class REAL = float>

struct Line
{
	typedef REAL IntersectionResult;
	typedef Vector3<REAL> V3;


	V3 p;
	V3 dir;

    Line(const V3& vP, const V3& vDirection): p(vP), dir(vDirection) { }

	bool operator           ==(const Line& l)  const { return (p == l.p) && (dir == l.dir); }
	bool operator           != (const Line& l) const { return !operator==(l); }

	void                    Normalize() { dir.normalize(); }

	V3                      GetPoint(const REAL& t) const
    {
		return Vector3<REAL>(p+dir*t);
	}
};

#endif
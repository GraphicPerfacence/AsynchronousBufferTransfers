
#include "../include/math3d.h"

float m3dGetVectorLengthSquared3(const Vec3f& u)
{
	return (u[0] * u[0]) + (u[1] * u[1]) + (u[2] * u[2]);
}

float m3dGetVectorLength3(const Vec3f& u)
{
	return sqrtf(m3dGetVectorLengthSquared3(u));
}

void m3dScaleVector3(Vec3f &v, const float scale)
{
	v[0] *= scale; v[1] *= scale; v[2] *= scale;
}

void m3dNormalizeVector3(Vec3f& u)
{
	m3dScaleVector3(u, 1.0f / m3dGetVectorLength3(u));
}

bool m3dCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon)
{
	return (std::fabs(fCandidate - fCompare) < fEpsilon);
}

bool is_near(float v1, float v2)
{
	return fabs(v1 - v2) < 0.01f;
}

float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}
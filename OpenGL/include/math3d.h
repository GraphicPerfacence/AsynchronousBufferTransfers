#include <math.h>

#include <glm/glm.hpp>


// Useful constants
#define M3D_PI (3.14159265358979323846)
#define M3D_2PI (2.0 * M3D_PI)
#define M3D_PI_DIV_180 (0.017453292519943296)
#define M3D_INV_PI_DIV_180 (57.2957795130823229)


typedef glm::vec2	Vec2f;		// 3D points = 3D Vectors, but we need a 
typedef double	M3DVector2d;		// 2D representations sometimes... (x,y) order

typedef glm::vec3	Vec3f;		// Vector of three floats (x, y, z)
typedef double	M3DVector3d[3];		// Vector of three doubles (x, y, z)

typedef glm::vec4	Vec4f;		// Lesser used... Do we really need these?
typedef double	M3DVector4d[4];		// Yes, occasionaly we do need a trailing w component

typedef glm::mat4  Matrix;


float m3dGetVectorLengthSquared3(const Vec3f& u);

float m3dGetVectorLength3(const Vec3f& u);

void m3dScaleVector3(Vec3f& v, const float scale);

void m3dNormalizeVector3(Vec3f& u);

bool m3dCloseEnough(const float fCandidate, const float fCompare, const float fEpsilon);

bool is_near(float v1, float v2);

float lerp(float a, float b, float f);

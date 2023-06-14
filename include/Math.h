#ifndef _MATH_M_H_
#define _MATH_M_H_

#include <cmath>
#include "Vector3.h"
typedef Vector3 vec3;
const static float PI = 3.14159f;

inline float GetDistance(vec3& p0, vec3& p1)
{
    return (p0 - p1).Length();
}
inline float cos(vec3& v1, vec3& v2)
{
    return (v1 * v2) / v1.Length() / v2.Length();
}
inline float sin(vec3& v1, vec3& v2)
{
    float c = cos(v1,v2);
    return sqrt(1.0 - c * c);
}
inline vec3 dot(vec3& v1, vec3& v2)
{
    return v1 * v2;
}
inline vec3 cross(vec3 v1, vec3 v2)
{
    return v1.cross(v2);
}

#endif

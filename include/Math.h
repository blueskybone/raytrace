#ifndef _MATH_M_H_
#define _MATH_M_H_

#include <cmath>
#include <random>
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
    vec3 v3 = v1 ^ v2;
    return (v1 ^ v2).Length()/ v1.Length() / v2.Length();
}
inline vec3 dot(vec3& v1, vec3& v2)
{
    return v1 * v2;
}
inline vec3 cross(vec3 v1, vec3 v2)
{
    return v1.cross(v2);
}
inline vec3 randomVec3(float min, float max)
{
   std::uniform_real_distribution<> dis(min,max);
   std::random_device rd;
   std::mt19937 gen(rd());
   float x = dis(rd);
   float y = dis(rd);
   float z = dis(rd);
   return vec3(x, y, z).norm();
}
inline float max(float v1, float v2, float v3)
{
    float a = std::max(v1, v2);
    return std::max(a, v3);
}
inline float min(float v1, float v2, float v3)
{
    float a = std::min(v1, v2);
    return std::min(a, v3);
}
#endif

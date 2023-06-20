#ifndef _RAYTRACE_H_
#define _RAYTRACE_H_
#include "Scene.h"
#include "Vector3.h"
#include "Math.h"
#include "Octree.h"
#include <cmath>

//判断八叉树相交情况
//bool Intersect(Ray inR, Octree oc)

//判断是否与mesh有交点
bool Intersect(Ray inR, Mesh &mesh);

//求光线与mesh的交点（多边形求完需要继续判断是否在mesh内）
vec3 InterPoint(Ray inR, Mesh& mesh);

//求反射光(理想情况)
Ray ReflRay(vec3& point, Ray inR, vec3 nor);

//是否发生全反射
//bool ToRefrRay(vec3& point, Ray inR, vec3& nor, float ior);

//求折射光
Ray RefrRay(vec3& point, Ray inR, vec3& nor, float ior);

//光追
vec3 Radiance(Scene* scene,int depth, Ray inR);

int toInt(float color);

Ray CameraRay(Scene *scene, int inx, int iny, float asp);

void Render(Scene * scene, vec3 * pix);

#endif
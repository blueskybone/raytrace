#include "Mesh.h"
#include "Math.h"
#include "Scene.h"
typedef Vector3 vec3;

Mesh::Mesh()
{
   meshType = MeshType::CIRCLE;
   matType = MatType::DIFF;
   radius = 5;
   v1 = vec3(0);
   v2 = vec3(0);
   v3 = vec3(0);
   vn = vec3(0, 1 ,0);
   position = vec3(0);
   emission = vec3(0);
   color = vec3(0.75);  //white
   rough = 0.5;
   refl = 0.2;
   //ior = 1;
}
Mesh::~Mesh()
{

}
bool Mesh::Contains(vec3 point)
{
    if (meshType == MeshType::CIRCLE)
    {
        return((point - position).Length() < radius);
    }
    if (meshType == MeshType::SPHERE)
    {
        return true;
    }
    if (meshType == MeshType::TRIANGEL)
    {
        vec3 vec0, vec1, vec2;
        vec3 v12,v23,v31;
        vec0 = point - v1;
        vec1 = point - v2;
        vec2 = point - v3;
        v12 = v2 - v1;
        v23 = v3 - v2;
        v31 = v1 - v3;
        float a = (vec0 ^ v12) * vec3(1);
        float b = (vec1 ^ v23) * vec3(1);
        float c = (vec2 ^ v31) * vec3(1);
        return (a < 0 && b < 0 && c < 0)||(a > 0 && b > 0 && c > 0);
       //return (a >= cos(PI/4.0))&&(b >= cos(PI/4.0)) &&(c <= cos(PI/2.0)) && (c >= cos(PI));
    }
    return false;
}

vec3 Mesh::NorVec(vec3 point)
{
    if(meshType == MeshType::CIRCLE)
    {
        //TODO
        return vn;
    }
    if(meshType == MeshType::SPHERE)
    {
        return (point - position).norm();
    }
    if(meshType == MeshType::TRIANGEL)
    {
        //return cross
        return vn;
    }
    return vec3(0);   
}

vec3 Mesh::NorVec(vec3 start, vec3 end)
{
   if(meshType == MeshType::CIRCLE || meshType == MeshType::TRIANGEL){
        vec3 vecn = vn;
        vec3 op = end - start;
        vecn = (op * vecn > 0)? vecn : vec3(0) - vecn;
        return vecn.norm();
    }
    else if(meshType == MeshType::SPHERE){
        vec3 vec = start - position;
        return vec.norm();
    }
    return vec3(0);
}


void Mesh::CalNorVec()
{
    if(meshType == MeshType::TRIANGEL)
    {
        vec3 l1 ,l2;
        l1 = v1 - v3;
        l2 = v2 - v3;
        vn = (l1 ^ l2).norm();
    }
}

float Mesh::max_x()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.x + radius;
    else if(meshType == MeshType::TRIANGEL)
    return max(v1.x, v2.x, v3.x);
}

float Mesh::max_y()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.y + radius;
    else if(meshType == MeshType::TRIANGEL)
    return max(v1.y, v2.y, v3.y);
}

float Mesh::max_z()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.z + radius;
    else if(meshType == MeshType::TRIANGEL)
    return max(v1.z, v2.z, v3.z);
}

float Mesh::min_x()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.x - radius;
    else if(meshType == MeshType::TRIANGEL)
    return min(v1.x, v2.x, v3.x);
}
float Mesh::min_y()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.y - radius;
    else if(meshType == MeshType::TRIANGEL)
    return min(v1.y, v2.y, v3.y);
}
float Mesh::min_z()
{
    if(meshType == MeshType::CIRCLE || meshType == MeshType::SPHERE)
    return position.z - radius;
    else if(meshType == MeshType::TRIANGEL)
    return min(v1.z, v2.z, v3.z);
}
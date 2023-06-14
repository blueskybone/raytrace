#include "RayTrace.h"
#include <stdio.h>
#include <vector>
typedef Vector3 vec3;

//bool Intersect(Ray inR, Octree oc)

//check if ray cross mesh's plane
bool Intersect(Ray inR, Mesh &mesh)
{
    if(mesh.meshType == MeshType::CIRCLE){
        if(mesh.vn * inR.dir == 0) return false;
        vec3 vn = mesh.vn;
        vec3 op = inR.start - mesh.position;
        vn = (op * vn > 0)? vn : vec3(0) - vn;
        return (inR.dir * vn < 0);
    }
    else if(mesh.meshType == MeshType::TRIANGEL){
        if(mesh.vn * inR.dir == 0) return false;
        vec3 vn = mesh.vn;
        vec3 op = inR.start - mesh.v1;
        vn = (op * vn > 0)? vn : vec3(0) - vn;
        return (inR.dir * vn < 0);
    }
    else if(mesh.meshType == MeshType::SPHERE){
        vec3 vec = mesh.position - inR.start;
        return (vec.Length() * sin(inR.dir, vec) <= mesh.radius);
    }
    else{
        exit(0);
    }
    return false;
}

bool Interscet(Ray inR, float length, Mesh& mesh)
{
    if(mesh.meshType == MeshType::CIRCLE){
        if(mesh.vn * inR.dir == 0) return false;
        vec3 vn = mesh.vn;
        vec3 op = inR.start - mesh.position;
        vn = (op * vn > 0)? vn : vec3(0) - vn;
        if(inR.dir * vn < 0)
        {
            vec3 p = InterPoint(inR, mesh);
            return p.Length() < length;
        } 
        return false;
    }
    else if(mesh.meshType == MeshType::TRIANGEL){
        if(mesh.vn * inR.dir == 0) return false;
        vec3 vn = mesh.vn;
        vec3 op = inR.start - mesh.v1;
        vn = (op * vn > 0)? vn : vec3(0) - vn;
        if(inR.dir * vn < 0)
        {
            vec3 p = InterPoint(inR, mesh);
            return p.Length() < length;
        } 
        return false;
    }
    else if(mesh.meshType == MeshType::SPHERE){
        vec3 vec = mesh.position - inR.start;
        if(vec.Length() * sin(inR.dir, vec) <= mesh.radius)
        {
            vec3 p = InterPoint(inR, mesh);
            return p.Length() < length;
        }
        return false;
    }
    else{
        exit(0);
    }
    return false;
}

bool InterPoint(Ray inR, Mesh& mesh, vec3 &point)
{
    if(mesh.meshType == MeshType::CIRCLE){
        vec3 d = inR.dir.norm();
        vec3 pq = mesh.position - inR.start;
        vec3 p = inR.start +  d * ((pq * mesh.vn) / (d * mesh.vn));
        float dis = (p - mesh.position).Length();
        if(dis <= mesh.radius)
        {
            point = p;
            /*
            point->x = p.x;
            point->y = p.y;
            point->z = p.z;
            */
            return true;
        }
        return false;
    }
    else if(mesh.meshType == MeshType::TRIANGEL){
        vec3 s = inR.start - mesh.v1;
        vec3 e1 = mesh.v2 - mesh.v1;
        vec3 e2 = mesh.v3 - mesh.v1;
        vec3 s1 = inR.dir.norm() ^ e1;
        vec3 s2 = s ^ e1;

        float s1e1 = s1 * e1;
        float t = s2 * e2/ s1e1;
        float b1 = s1 * s/ s1e1;
        float b2 = s2 * inR.dir.norm() / s1e1;
        if(t >= 0.f && b1 >= 0.f && b2 >= 0.f && (1 - b1 - b2) >= 0.f)
        {
            point = inR.start + inR.dir.norm() * t;
            return true;
        }
        return false;
    }
    else if(mesh.meshType == MeshType::SPHERE){
        vec3 vec = mesh.position - inR.start;
        if(vec.Length() * sin(inR.dir, vec) <= mesh.radius)
        {
            vec3 l = mesh.position - inR.start;
            vec3 d = inR.dir.norm();
            float s = l * d;
            float m = l * l - s * s;
            float q = sqrt( mesh.radius * mesh.radius - m);
            float t = s - q;
            point = inR.start + d * t;
            return true;
        }
        return false;

        return false;
    }
    else{
        exit(0);
    }
    return false;   
}

//calculate the point cross with mesh's plane
vec3 InterPoint(Ray inR, Mesh& mesh)
{
    if(mesh.meshType == MeshType::CIRCLE)
    {
        vec3 t = mesh.position - inR.start;
        float d = t.Length() * fabsf(cos(t, mesh.vn));
        float s = d / fabsf(cos(inR.dir, mesh.vn));
        vec3 vec = inR.dir * (s/inR.dir.Length());
        vec3 point = inR.start + vec;
        return point;
    }
    else if(mesh.meshType == MeshType::TRIANGEL)
    {
        vec3 t = mesh.v1 - inR.start;
        float d = t.Length() * fabsf(cos(t, mesh.vn));
        float s = d / fabsf(cos(inR.dir, mesh.vn));
        vec3 vec = inR.dir * (s/inR.dir.Length());
        vec3 point = inR.start + vec;
        return point;
    }
    else if(mesh.meshType == MeshType::SPHERE)
    {
        vec3 l = mesh.position - inR.start;
        vec3 d = inR.dir.norm();
        float s = l * d;
        float m = l * l - s * s;
        float q = sqrt( mesh.radius * mesh.radius - m);
        float t = s - q;
        return inR.start + d * t;
    }
    else return vec3(0);
}
//calculate reflect ray
Ray ReflRay(vec3& point, Ray inR, vec3 nor)
{
    //R=L-2(N*L)*N
    vec3 l = inR.dir.norm();
    vec3 n = nor.norm();
    vec3 r = l - (n *(n * l)) * 2;
    return Ray(point, r);
}

//check if refract ray exist
/*
bool ToRefrRay(vec3& point, Ray inR, vec3& nor, float ior)
{
    float cos1 = fabsf(cos (inR.dir, nor));
    float cos = sqrt(1 - ior*ior);
    return cos1 > cos;
}*/

//calculate refract ray
/*
Ray RefrRay(vec3& point, Ray inR, vec3& nor, float ior)
{
    float cos1 = fabsf(cos (inR.dir, nor));
    float cos2 = sqrt(1.0 - (1.0 / (ior * ior) ) * (1 - cos1*cos1));
    vec3 vec = inR.dir/ior + nor * (cos1/ior - cos2);
    return Ray(point, vec);
}
*/

bool inShadow(vec3 point, Mesh light, Scene * scene)
{
    vec3 lit = light.position - point;
    vec3 s = point + lit.norm() * 10;
    vec3 d = lit; 
    for(int meshID = 0; meshID < scene->meshes.size();meshID++)
    {
        if(Intersect(Ray(s,d), scene->meshes[meshID]))
        {
         vec3 p = InterPoint(Ray(s,d), scene->meshes[meshID]);
         if(scene->meshes[meshID].Contains(p))
         {
            if(scene->meshes[meshID].matType == MatType::LITE) {
                continue;
            }
            else {
                return true;
            }
         }
        }
    }
    return false;
}

//lambert
vec3 Lambert(vec3 point, Mesh light, vec3 nor, Scene * scene)
{
    vec3 lit = light.position - point;
    //vec3 s = point + nor * 2;
    return light.emission * cos(lit, nor) * light.rough; 
}

//blind-phone
vec3 Phone(vec3 point, Mesh light, vec3 nor, Ray inR)
{
    vec3 lit = light.position - point;
    vec3 h = lit - inR.dir;
    float cos1 = cos(h,nor);
    return light.emission * light.refl * pow(cos1,2); 
}
vec3 Radiance(Scene* scene,int depth, Ray inR)
{
    if(depth > scene->renderer->maxDepth) return vec3(0);      //return black

    int meshID;
    Mesh mesh;
    std::vector<Mesh> meshes;
    std::vector<vec3> points;
    vec3 point;
    //view depth
    for (meshID = 0; meshID < scene->meshes.size(); meshID++)
    {
        Mesh mesh = scene->meshes[meshID];
        if(Intersect(inR, mesh))
        {
            vec3 point = InterPoint(inR, mesh);
            if(mesh.Contains(point)) 
            {
                meshes.push_back(mesh);
                points.push_back(point);
            }
        }
    }
    if(0 == meshes.size()) return vec3(0);                  //miss hit return black
    if(1 == meshes.size()==1)
    {
        point = points[0];
        mesh  = meshes[0];
    }
    else
    {
        meshID = 0;
        float min_l = 10000.0;
        for(int i = 0;i<points.size();i++)
        {
            float len = (inR.start - points[i]).Length();
            if(len < min_l)
            {
                meshID = i;
                min_l = len;
            }
        }
        mesh = meshes[meshID];
        point = points[meshID];
    }

    if(mesh.matType == MatType::LITE) return mesh.emission;          //return light
    else if(mesh.matType == MatType::DIFF)                           //bline-phone model
    {
        //TODO: 漫反射材质不应该有高光，重新考虑rough和refl参数的意义
        //漫反射光追：随机发射线条（蒙特卡洛积分）。
        vec3 local = vec3(0);
        for(int i = 0; i<scene->lights.size(); i++)
        {
            Mesh light = scene->lights[i];

            if(inShadow(point,light, scene)) 
            {
                local -= vec3(0.5);
            }              //ignore light
            vec3 lam = Lambert(point, light, mesh.NorVec(point, light.position),scene);
            vec3 pho = Phone(point, light, mesh.NorVec(point, light.position), inR);
            local += lam; local += pho;
        }          
        Ray refl = ReflRay(point, inR, mesh.NorVec(point));
        vec3 refle = Radiance(scene, depth + 1, refl);
        vec3 c = mesh.color.cross(local);
        return c + refle * mesh.refl;
    }
    else if(mesh.matType == MatType::REFL)          
    {
        Ray refl = ReflRay(point, inR, mesh.NorVec(point));
        vec3 refle = Radiance(scene, depth + 1, refl);
        return refle * 1;
    }
    else return vec3(0);
}

//暂不计算lookat
Ray CameraRay(Scene *scene, int inx, int iny, float asp)
{

    float theta = scene->camera->fov / 180 * PI;
    float z = 1/tan(theta/2);
    float x = asp*(1 - float(inx) * 2.0 / float(scene->renderer->width));
    float y = 1 - float(iny) * 2.0 / float(scene->renderer->height);
    return Ray(scene->camera->position, vec3(x, y, z));
}
int toInt(float color)
{
    color = (color <= 1)? color : 1;
    return int( color * 255);
}

//光线跟踪
void Render(Scene * scene, vec3 * pix)
{
    int h = scene->renderer->height;
    int w = scene->renderer->width;
    float asp = 1.0 * w/h;
    for(int i = 0;i < h; i++)
        for(int j = 0; j < w; j++)
        {
            Ray inR = CameraRay(scene, j, i, asp);
            vec3 c = Radiance(scene,1,inR);
            pix[i*w+j].x = c.x;
            pix[i*w+j].y = c.y;
            pix[i*w+j].z = c.z;
        }
}
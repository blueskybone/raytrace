#ifndef _MESH_H_
#define _MESH_H_

#include "Vector3.h"


  enum MeshType
    {
        CIRCLE,
        SPHERE,
        TRIANGEL
    };
    enum MatType
    {
        DIFF,
        REFL,
        LITE
    };
class Mesh
{
    public:
    float   meshType;
    float   matType;

    float   radius;
    vec3    v1,v2,v3,vn;

    vec3    position;
    vec3    emission;
    vec3    color;
    float    rough;
    float    refl;
    //float    ior;

    public:
    Mesh();
    ~Mesh();
    bool Contains(vec3 point);
    void CalNorVec();
    vec3 NorVec(vec3 point);
    vec3 NorVec(vec3 start, vec3 end);
    float max_x();
    float max_y();
    float max_z();
    float min_x();
    float min_y();
    float min_z();
};

#endif
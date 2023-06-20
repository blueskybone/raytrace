#ifndef _OCTREE_H_
#define _OCTREE_H_

#include "Vector3.h"
#include "Mesh.h"
#include <vector>
#include <stdio.h>
struct AABB
{
    /* data */
    vec3 max;
    vec3 min;
    public:
    AABB(){}
    AABB(float max_x, float max_y, float max_z, float min_x, float min_y, float min_z)
    {
        max = vec3(max_x,max_y,max_z);
        min = vec3(min_x,min_y,min_z);
    }
    bool Contains(vec3 p)
    {
        if(p.x <= max.x && p.x >= min.x &&
        p.y <= max.y && p.y >= min.y &&
        p.z <= max.z && p.z >= min.z) return true;
        else return false;
    }
    void Print()
    {
        printf("%.2f %.2f %.2f %.2f %.2f %.2f\n", max.x,max.y,max.z,min.x,min.y,min.z);
    }
};


class Octree
{
    public:
    AABB node;
    std::vector<int> meshID;
    bool isLeaf;
    Octree *nodes[8];

    public:
    Octree();
    ~Octree();
    void buildAABB(AABB aabb);
    void buildChild();
    bool Contains(Mesh mesh);
};

#endif
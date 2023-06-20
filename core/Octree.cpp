#include "Octree.h"

Octree::Octree()
{
    isLeaf = false;
}

void Octree::buildAABB(AABB aabb)
{
    node = aabb;
}
void Octree::buildChild()
{
    //AABB ab;
    vec3 mid = (node.max + node.min)/2;
    float mid_x = mid.x;
    float mid_y = mid.y;
    float mid_z = mid.z;
    AABB ab[8];
    ab[0] = AABB(node.max.x, node.max.y, node.max.z, mid_x, mid_y, mid_z);
    ab[1] = AABB(mid_x, node.max.y, node.max.z, node.min.x, mid_y, mid_z);
    ab[2] = AABB(node.max.x, node.max.y, mid_z, mid_x, mid_y, node.min.z);
    ab[3] = AABB(mid_x, node.max.y, mid_z, node.min.z, mid_y, node.min.z);
    ab[4] = AABB(node.max.x, mid_y, node.max.z, mid_x, node.min.y, mid_z);
    ab[5] = AABB(mid_x, mid_y, node.max.z, node.min.x, node.min.y, mid_z);
    ab[6] = AABB(node.max.x, mid_y, mid_z, mid_x, node.min.y, node.min.z);
    ab[7] = AABB(mid_x, mid_y, mid_z, node.min.z, node.min.y, node.min.z);
    for(int i = 0; i< 8;i++)
    {
        nodes[i] = new Octree();
        nodes[i]->node = ab[i];
    }
}

bool Octree::Contains(Mesh mesh)
{
    if(mesh.meshType == MeshType::TRIANGEL)
    {
        if(node.Contains(mesh.v1)||node.Contains(mesh.v2)||node.Contains(mesh.v3)) return true;
        else return false;
    }
    else if(mesh.meshType == MeshType::CIRCLE||mesh.meshType == MeshType::SPHERE)
    {
        vec3 p1(mesh.max_x(),mesh.max_y(),mesh.max_z());
        vec3 p2(mesh.min_x(),mesh.min_y(),mesh.min_z());
        if(node.Contains(p1)||node.Contains(p2)) return true;
        else return false;
    }
    return false;
   
}
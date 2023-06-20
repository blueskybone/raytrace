#include "Scene.h"
#include <iostream>
typedef Vector3 vec3;
Scene::Scene()
{
    meshes.clear();
    lights.clear();
}
Scene::~Scene()
{
    if(camera != nullptr)delete camera;
    if(renderer != nullptr)delete renderer;
    meshes.clear();
}

bool Scene::AddCamera(vec3 pos, vec3 lookAt, float fov)
{
    if(camera != nullptr){
        delete camera;
    }   
    camera = new Camera();
    camera->position = pos;
    camera->lookAt = lookAt;
    camera->fov = fov;
    return true;
}
bool Scene::AddRenderer(int width, int height, int maxDepth)
{
    if(renderer != nullptr){
        delete renderer;
    }   
    renderer = new Renderer();
    renderer->width = width;
    renderer->height = height;
    renderer->maxDepth = maxDepth;
    return true;
}

int Scene::AddMesh(Mesh mesh)
{
    mesh.CalNorVec();
    meshes.push_back(mesh);
    if(mesh.matType == MatType::LITE) lights.push_back(mesh); 
    return meshes.size() -1;
}

bool Scene::BuildOctree()
{
    float min_x = 10000.0, min_y = 10000.0, min_z = 10000.0;
    float max_x = -10000.0, max_y = -10000.0, max_z = -10000.0;
    for(int i = 0;i<meshes.size();i++)
    {
        float maxx = meshes[i].max_x();
        float maxy = meshes[i].max_y();
        float maxz = meshes[i].max_z();
        float minx = meshes[i].min_x();
        float miny = meshes[i].min_y();
        float minz = meshes[i].min_z();
        if(maxx > max_x) max_x = maxx;
        if(maxy > max_y) max_y = maxy;
        if(maxz > max_z) max_z = maxz;
        if(minx < min_x) min_x = minx;
        if(miny < min_y) min_y = miny;
        if(minz < min_z) min_z = minz;
    }

    printf("%.2f %.2f %.2f %.2f %.2f %.2f\n", max_x,max_y,max_z,min_x,min_y,min_z);
    root = new Octree();
    root->node = AABB(max_x, max_y, max_z, min_z, min_y, min_z);

    BuildTree(root,0);
    return true;
}

//终止条件：包含小于2个mesh，或树的深度到达4
void Scene::BuildTree(Octree * tree, int depth)
{
    if( depth >= 4) 
    {
        for(int i = 0; i < meshes.size(); i++)
        {
            if(tree->Contains(meshes[i]))
            {
                tree->meshID.push_back(i);
                printf("depth:ID: %d\n", i);
            }
        }
        tree->isLeaf = true;
        return;
    }
    int r = 2;
    int cnt = 0;
    for(int i = 0; i < meshes.size(); i++)
    {
        if(cnt > r) break;
        if(tree->Contains(meshes[i]))
        {
            tree->meshID.push_back(i);
            printf("leaf:ID: %d\n", i);
            cnt++;
        }
    }
    if(tree->meshID.size() <= r)
    {
        tree->isLeaf = true;
        return;
    }
    else
    {
        tree->buildChild();
        for(int i = 0;i<8;i++)
        {
            BuildTree(tree->nodes[i], depth+1);
        }
    }
}
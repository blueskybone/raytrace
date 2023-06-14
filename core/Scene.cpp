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
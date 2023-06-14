#ifndef _SCENE_H_
#define _SCENE_H_

#include "Mesh.h"
#include "Math.h"
#include "Vector3.h"
#include <vector>

struct Ray
{
    vec3 start;
    vec3 dir;
    public:
    Ray();
    Ray(vec3 s, vec3 d)
    {
        start = s;
        dir = d;
    }
};
struct Renderer
{
    int width;
    int height;
    int maxDepth;
};
struct Camera
{
    vec3 position;
    vec3 lookAt;
    float fov;
};

class Scene
{
    public:
        Scene();
        ~Scene();

        bool AddCamera(vec3 pos, vec3 lookAt, float fov);
        bool AddRenderer(int width, int height, int maxDepth);
        int AddMesh(Mesh mesh);
        //bool BuildOctree();

    public:
        std::vector<Mesh>   meshes;
        std::vector<Mesh>   lights;
        Camera*             camera = nullptr;
        Renderer*           renderer = nullptr;
    private:
        //octree *octree;
};
#endif
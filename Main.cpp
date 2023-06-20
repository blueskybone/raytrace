#include <iostream>
#include <string>
#include "Scene.h"
#include "RayTrace.h"
#include "SceneLoader.h"
#include "RayTrace.h"
#include "ImgWriter.h"

Scene *scene    = nullptr;
vec3 * pix      = nullptr;

void InitScene()
{
    if(scene!=nullptr)
    {
        delete scene;
        scene = new Scene();
    }
    else scene = new Scene();
}
void InitImg(Scene * scene, vec3 * pix[])
{
    int w = scene->renderer->width;
    int h = scene->renderer->height;
    // if(pix != nullptr)
    // {
    //     delete[] pix;
    //     *pix = new vec3[w*h];
    // }
    *pix = new vec3[w*h];
}

int main()
{
    const std::string filename = "scene.scene";

    InitScene();

    if(!LoadSceneFromFile(filename, scene))return 0;

    if(!CheckScene(scene)) return 0;

    BuildOctree(scene);

    InitImg(scene, &pix);

    //std::cout<<"load file suc.";

    Render(scene, pix);
    
    WriteToFile(scene, pix);

    return 0;
}
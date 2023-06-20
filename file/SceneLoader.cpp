#include <string.h>
#include "SceneLoader.h"

typedef Vector3 vec3;

bool LoadSceneFromFile(const std::string& filename, Scene* scene)
{
    static const int s_MAX_LINE_LENGTH = 2048;
    FILE* file = fopen(filename.c_str(), "r");
    if (!file)
    {
        printf("Couldn't open %s for reading\n", filename.c_str());
        return false;
    }
    printf("Loading file...\n");
    char line[s_MAX_LINE_LENGTH];
    while (fgets(line, s_MAX_LINE_LENGTH, file))
    {
        if(line[0] == '#') continue;
        char name[s_MAX_LINE_LENGTH] = { 0 };
        //--------------------------------------------
        // Camera
        if (strstr(line, "Camera"))
        {
            vec3 position;
            vec3 lookAt;
            float fov;
            while (fgets(line, s_MAX_LINE_LENGTH, file))
            {
				if (strchr(line, '}')) break;
                sscanf(line, "position %f %f %f", &position.x, &position.y, &position.z);
                sscanf(line, "lookAt %f %f %f", &lookAt.x, &lookAt.y, &lookAt.z);
                sscanf(line, "fov %f", &fov);
            }
            scene->AddCamera(position, lookAt, fov);
        }
        //--------------------------------------------
        // Renderer
        else if (strstr(line, "Renderer"))
        {
            int width,height;
            int maxDepth;
            while (fgets(line, s_MAX_LINE_LENGTH, file))
            {
		        if (strchr(line, '}')) break;

                sscanf(line, "resolution %d %d", &width, &height);
                sscanf(line, "maxDepth %d", &maxDepth);
            }
            scene->AddRenderer(width,height,maxDepth);
        }
        //--------------------------------------------
        // Mesh
        else if (strstr(line, "Mesh"))
        {
            Mesh mesh;
            char meshType[20] = "None";
            char matType[20] = "None";
            while (fgets(line, s_MAX_LINE_LENGTH, file))
            {
				if (strchr(line, '}')) break;
                sscanf(line, "type %s", meshType);  
                sscanf(line, "material %s", matType);  
                sscanf(line, "position %f %f %f ", &mesh.position.x, &mesh.position.y, &mesh.position.z);
                sscanf(line, "v1 %f %f %f", &mesh.v1.x, &mesh.v1.y, &mesh.v1.z);
                sscanf(line, "v2 %f %f %f", &mesh.v2.x, &mesh.v2.y, &mesh.v2.z);
                sscanf(line, "v3 %f %f %f", &mesh.v3.x, &mesh.v3.y, &mesh.v3.z);
                sscanf(line, "vn %f %f %f", &mesh.vn.x, &mesh.vn.y, &mesh.vn.z);
                sscanf(line, "radius %f", &mesh.radius);
                sscanf(line, "emission %f %f %f", &mesh.emission.x, &mesh.emission.y,&mesh.emission.z);
                sscanf(line, "color %f %f %f", &mesh.color.x, &mesh.color.y,&mesh.color.z);
                sscanf(line, "roughness %f",&mesh.rough);
                sscanf(line, "refl %f",&mesh.refl);
            }
            if (strcmp(meshType, "CIRCLE") == 0){
                mesh.meshType = MeshType::CIRCLE;
            } 
            else if(strcmp(meshType, "SPHERE") == 0){
                mesh.meshType = MeshType::SPHERE;
            }
            else if(strcmp(meshType, "TRIANGEL")== 0){
                mesh.meshType = MeshType::TRIANGEL;
            }

            if(strcmp(matType,"DIFF") == 0){
                mesh.matType = MatType::DIFF;
            }
            else if(strcmp(matType,"LITE") == 0){
                mesh.matType = MatType::LITE;
            }
            else if(strcmp(matType,"REFL") == 0){
                mesh.matType = MatType::REFL;
            }

            scene->AddMesh(mesh);
        }
    }
    fclose(file);
    printf("Load done.\n");
    return true;
}

bool CheckScene(Scene * scene)
{
    if(scene->camera == nullptr){
        printf("no Camera loaded.\n will exit.\n");
        return false;
    }
    if(scene->renderer == nullptr){
        printf("no renderer loaded.\n will exit.\n");
        return false;
    }
    if(scene->meshes.size() == 0){
        printf("no meshes loaded.\n will exit.\n");
        return false;
    }
    return true;
}

void BuildOctree(Scene * scene)
{
    scene->BuildOctree();
}

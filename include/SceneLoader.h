#ifndef _SCENELOADER_H_
#define _SCENELOADER_H_

#include "Scene.h"
#include "Vector3.h"
#include <string>

bool LoadSceneFromFile(const std::string&filename, Scene* scene);

bool CheckScene(Scene * scene);

#endif
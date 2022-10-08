//
// Created by daniel on 10/8/22.
//

#ifndef OGL_TST_02_SCENEMANAGER_H
#define OGL_TST_02_SCENEMANAGER_H


#include <vector>
#include "Scene.h"
/*
 *
 * To be implemented
 *
 * */
class SceneManager {
private:
    Scene* current;
    std::vector<Scene*> scenes;
public:
    SceneManager() = default;
    ~SceneManager() = default;
    Scene* getCurrent();
};


#endif //OGL_TST_02_SCENEMANAGER_H

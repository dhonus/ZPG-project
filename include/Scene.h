//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_SCENE_H
#define OGL_TST_02_SCENE_H

#include "Window.h"
#include "Object.h"
#include "Camera.h"
#include "Callbacks.h"
#include "Hud.h"
class Hud;
class Object;
class Callbacks;
class Scene {
public:
    Scene(std::shared_ptr<Window> t_window, int width, int height);
    ~Scene();
    std::vector<std::shared_ptr<Object>> objects;
    int render();
private:
    Camera* camera;
    std::unique_ptr<Hud> hud;
    Callbacks* callbacks;
    std::shared_ptr<Window> window;
    std::shared_ptr<Object> addObjectToScene(std::shared_ptr<Object> object);
};


#endif //OGL_TST_02_SCENE_H

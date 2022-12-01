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
#include "Light.h"
#include "../models/tree.h"

class Hud;
class Object;
class Callbacks;
class Scene : Observer{
public:
    Scene(std::shared_ptr<Window> t_window, int width, int height);
    ~Scene();
    std::vector<std::shared_ptr<Object>> objects;
    int render();
    std::shared_ptr<Object> addObjectToScene(std::shared_ptr<Object> object);
    void update(Subject &s);
private:
    Callbacks* callbacks;
    std::shared_ptr<Window> window;
    int object_id = 0;
protected:
    std::vector<std::shared_ptr<Light>> lights;
    Camera* camera;
    std::unique_ptr<Hud> hud;
};


#endif //OGL_TST_02_SCENE_H

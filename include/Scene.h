//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_SCENE_H
#define OGL_TST_02_SCENE_H

#include "Window.h"
#include "Object.h"


class Scene {
public:
    Scene(std::shared_ptr<Window> t_window);
    std::vector<std::unique_ptr<Object>> objects;
    int render();
private:
    std::shared_ptr<Window> window;
    std::vector<float> b{
            -.8f, -.5f, .5f, 1, 1, 2, 0, 1,
            -.8f, .5f, .5f, 1, 1, 2, 0, 1,
            .8f, .5f, .5f, 1, 0, 2, 0, 1,
            .8f, -.5f, .5f, 1, 0, 2, 0, 1
    };
    std::vector<float> b2{
        -.5f, -.5f, .5f, 1, 1, 1, 0, 1,
        -.5f, .5f, .5f, 1, 1, 0, 0, 1,
        .5f, .5f, .5f, 1, 0, 0, 0, 1,
        .5f, -.5f, .5f, 1, 0, 1, 0, 1
    };
};


#endif //OGL_TST_02_SCENE_H

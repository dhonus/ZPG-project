//
// Created by daniel on 11/30/22.
//

#ifndef ZPG_OPENWORLDSCENE_H
#define ZPG_OPENWORLDSCENE_H

#include "../Scene.h"


class OpenWorldScene : public Scene {
public:
    OpenWorldScene(std::shared_ptr<Window> t_window, int width, int height) : Scene(t_window, width, height) {

    }
    ~OpenWorldScene();
    int render();
    void update(Subject &s);
};

#endif //ZPG_OPENWORLDSCENE_H

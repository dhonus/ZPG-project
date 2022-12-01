//
// Created by daniel on 11/30/22.
//

#ifndef ZPG_OPENWORLDSCENE_H
#define ZPG_OPENWORLDSCENE_H

#include "../Scene.h"

class OpenWorldScene : public Scene {
public:
    OpenWorldScene(std::shared_ptr<Window> t_window, int width, int height);
};

#endif //ZPG_OPENWORLDSCENE_H

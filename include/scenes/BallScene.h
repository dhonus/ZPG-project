//
// Created by daniel on 1.12.22.
//

#ifndef ZPG_BALLSCENE_H
#define ZPG_BALLSCENE_H

#include <memory>
#include "../Scene.h"

class BallScene : public Scene {
public:
    BallScene(std::shared_ptr<Window> t_window, int width, int height);
};

#endif //ZPG_BALLSCENE_H

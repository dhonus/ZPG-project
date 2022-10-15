//
// Created by daniel on 10/13/22.
//

#include <iostream>
#include "../include/Hud.h"

int Hud::draw(Camera* camera) {
    gltInit();

    GLTtext *text = gltCreateText();
    glm::vec3 pos = camera->pos();
    std::string position{};
    position += "x: " + std::to_string(pos[0]);
    position += "\ny: " + std::to_string(pos[1]);
    position += "\nz: " + std::to_string(pos[2]);
    gltSetText(text, position.c_str());

    gltBeginDraw();
    gltColor(1.0f, 1.0f, 1.0f, 0.0f);

    gltDrawText2D(text, 0, 0, 1.5);
    gltEndDraw();
    return 0;
}

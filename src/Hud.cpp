//
// Created by daniel on 10/13/22.
//

#include <iostream>
#include <chrono>
#include "../include/Hud.h"

int Hud::draw(Camera &camera) {
    static auto oldTime = std::chrono::high_resolution_clock::now();
    static int fps; fps++;
    static int appending_fps;

    if (std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now() - oldTime) >= std::chrono::milliseconds { 200 }) {
        oldTime = std::chrono::high_resolution_clock::now();
        appending_fps = fps;
        fps = 0;
    }

    gltInit();

    GLTtext *text = gltCreateText();
    glm::vec3 pos = camera.getPosition();
    std::string position{};
    position += "x: " + std::to_string(pos[0]);
    position += "\ny: " + std::to_string(pos[1]);
    position += "\nz: " + std::to_string(pos[2]);
    position += "\nFPS: " + std::to_string(appending_fps);
    gltSetText(text, position.c_str());

    gltBeginDraw();
    gltColor(1.0f, 1.0f, 1.0f, 1.0f);

    gltDrawText2D(text, 0, 0, 1.5);
    gltEndDraw();

    return 0;
}

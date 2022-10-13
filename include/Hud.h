//
// Created by daniel on 10/13/22.
//

#ifndef ZPG_HUD_H
#define ZPG_HUD_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define GLT_IMPLEMENTATION

#include "../lib/gltext.h" /* https://github.com/vallentin/glText */
#include "Camera.h"
#include <string>



class Hud {
public:
    int draw(Camera* camera);
};


#endif //ZPG_HUD_H

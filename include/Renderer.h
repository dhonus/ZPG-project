//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_RENDERER_H
#define OGL_TST_02_RENDERER_H

#include "Window.h"


class Renderer {
public:
    Renderer(Window *t_window);
    int render();
private:
    Window *window;
};


#endif //OGL_TST_02_RENDERER_H

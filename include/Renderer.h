//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_RENDERER_H
#define OGL_TST_02_RENDERER_H
#include "Window.h"


class Renderer {
private:
    Window* window;
    GLuint shaderProgram;
    GLuint VAO;
public:
    Renderer(Window* t_window, GLuint shaderProgram);
    int render();
};


#endif //OGL_TST_02_RENDERER_H

//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_WINDOW_H
#define OGL_TST_02_WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <glm/vec2.hpp>

class Window {
private:
    GLFWwindow *window;
    int major, minor, revision, width, height;
    float ratio;
    void error_callback(int error, const char *description) { fputs(description, stderr); }
public:
    Window(int width, int height);
    ~Window();
    GLFWwindow* getWindow();
    void get_version_info();
};


#endif //OGL_TST_02_WINDOW_H

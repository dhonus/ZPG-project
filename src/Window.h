//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_WINDOW_H
#define OGL_TST_02_WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>

class Window {
private:
    GLFWwindow* window;
    void error_callback(int error, const char* description){ fputs(description, stderr); }
    void init();
    int width, height;
    float ratio;
public:
    Window(){
        init();

        glViewport(0, 0, width, height);

        if (!glfwInit()) {
            fprintf(stderr, "ERROR: could not start GLFW3\n");
            exit(EXIT_FAILURE);
        }

        this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
        ratio = width / (float)height;

        glfwGetFramebufferSize(this->window, &width, &height);
        if (!this->window){
            glfwTerminate();
            exit(EXIT_FAILURE);
        }
        glfwMakeContextCurrent(this->window);
        glfwSwapInterval(1);
    }
    ~Window(){
        glfwDestroyWindow(this->window);
        glfwTerminate();
    }
    GLFWwindow* getWindow(){
        return this->window;
    }
};


#endif //OGL_TST_02_WINDOW_H

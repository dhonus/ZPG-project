//
// Created by daniel on 12.10.22.
//

#include "../include/Callbacks.h"

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void Callbacks::init() {

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    auto focused = [](GLFWwindow *window, int focused) {
        std::cout << "focused\n";
    };

    auto iconified = [](GLFWwindow *window, int iconified) {
        std::cout << "iconified\n";
    };

    auto windowSize = [](GLFWwindow *window, int width, int height){
        printf("resize %d, %d \n", width, height);
        glViewport(0, 0, width, height);
        instance().width = width;
        instance().height = height;
        camera->update(instance());
    };

    auto mouse = [](GLFWwindow * win, double x, double y) {
        if (!camera){
            std::cout << "camera not bound\n" << std::flush;
            return;
        }
        camera->mouse(x, y);
    };

    auto keyboard = [](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    };

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouse);
    glfwSetWindowSizeCallback(window, windowSize);
    glfwSetWindowIconifyCallback(window, iconified);
    glfwSetWindowFocusCallback(window, focused);
}

Callbacks::Callbacks(GLFWwindow* window) {
    this->window = window;
    this->init();
    this->callbacks = this;
}

Camera* Callbacks::camera = nullptr;
Callbacks* Callbacks::callbacks = nullptr;
float Callbacks::width = 0;
float Callbacks::height = 0;

void Callbacks::setCamera(Camera* t_camera) {
    Callbacks::camera = t_camera;
}

Callbacks &Callbacks::instance() {
    return *callbacks;
}

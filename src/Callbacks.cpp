//
// Created by daniel on 12.10.22.
//

#include "../include/Callbacks.h"

Camera* Callbacks::camera = nullptr;
Callbacks* Callbacks::callbacks = nullptr;

float Callbacks::width = 0;
float Callbacks::height = 0;

static auto errorCallback = [](int error, const char *description) {
    std::cout << description << std::flush;
    exit(-1);
};

void Callbacks::init() {

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    auto windowFocusedCallback = [](GLFWwindow *window, int focused) {
        std::cout << "windowFocusedCallback\n";
    };

    auto windowIconifiedCallback = [](GLFWwindow *window, int iconified) {
        std::cout << "windowIconifiedCallback\n";
    };

    auto windowSizeChangeCallback = [](GLFWwindow *window, int width, int height){
        std::cout << "resize W: " << width << " H: " <<  height << "\n" << std::flush;
        glViewport(0, 0, width, height);
        instance().width = width;
        instance().height = height;
        camera->update(instance());
    };

    auto mouseCallback = [](GLFWwindow *win, double x, double y) {
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

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetWindowSizeCallback(window, windowSizeChangeCallback);
    glfwSetWindowIconifyCallback(window, windowIconifiedCallback);
    glfwSetWindowFocusCallback(window, windowFocusedCallback);
}

Callbacks::Callbacks(GLFWwindow& window) {
    this->window = &window;
    this->init();
    this->callbacks = this;
}

void Callbacks::setCamera(Camera *&t_camera) {
    Callbacks::camera = t_camera;
}

Callbacks &Callbacks::instance() {
    return *callbacks;
}

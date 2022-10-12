//
// Created by daniel on 12.10.22.
//

#include <utility>

#include "../include/Callbacks.h"


static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

bool Callbacks::A = false;
bool Callbacks::B = false;

void Callbacks::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    //printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    if (key == GLFW_KEY_A) A = true;
    if (key == GLFW_KEY_B) B = true;
    if (A && B)
    {
        // now you know that both A and B keys are down, do what you need
        std::cout << "yay\n";
        A, B = false;
    }
}


void Callbacks::window_focus_callback(GLFWwindow *window, int focused) { printf("window_focus_callback \n"); }

void Callbacks::window_iconify_callback(GLFWwindow *window, int iconified) { printf("window_iconify_callback \n"); }

void Callbacks::window_size_callback(GLFWwindow *window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void Callbacks::cursor_callback(GLFWwindow *window, double x, double y) {

}

void Callbacks::button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void Callbacks::init() {

    auto mouse = [](GLFWwindow * win, double x, double y) {
        if (!camera){
            std::cout << "camera not bound\n" << std::flush;
            return;
        }
        camera->mouse(x,y);
    };
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, mouse);
    glfwSetWindowSizeCallback(window, window_size_callback);
    glfwSetKeyCallback(window, key_callback);
}

Callbacks::Callbacks(GLFWwindow* window) {
    this->window = window;
    this->init();
}
std::shared_ptr<Camera> Callbacks::camera = nullptr;

void Callbacks::setCamera(std::shared_ptr<Camera> t_camera) {
    Callbacks::camera = std::move(t_camera);
}

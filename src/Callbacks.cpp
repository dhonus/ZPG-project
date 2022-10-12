//
// Created by daniel on 12.10.22.
//

#include <utility>

#include "../include/Callbacks.h"


static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

bool Callbacks::W = false;
bool Callbacks::A = false;
bool Callbacks::S = false;
bool Callbacks::D = false;

void Callbacks::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {

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

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);
    auto mouse = [](GLFWwindow * win, double x, double y) {
        if (!camera){
            std::cout << "camera not bound\n" << std::flush;
            return;
        }
        camera->mouse(x,y);
    };
    auto keyboard = [](GLFWwindow *window, int key, int scancode, int action, int mods){
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);


        /*
        if (key == GLFW_KEY_W) W = true;
        if (key == GLFW_KEY_A) A = true;
        if (key == GLFW_KEY_S) S = true;
        if (key == GLFW_KEY_D) D = true;
        camera->move(W,S,A,D);
        W = false;
        A = false;
        S = false;
        D = false;
        // Move backward
        if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
            std::cout << "d";
        }
        // Strafe right
        if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
            std::cout << "l";
        }
        // Strafe left
        if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
            std::cout << "r";
        }
        */
    };

    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouse);
    glfwSetWindowSizeCallback(window, window_size_callback);
}

Callbacks::Callbacks(GLFWwindow* window) {
    this->window = window;
    this->init();
}
std::shared_ptr<Camera> Callbacks::camera = nullptr;

void Callbacks::setCamera(std::shared_ptr<Camera> t_camera) {
    Callbacks::camera = std::move(t_camera);
}

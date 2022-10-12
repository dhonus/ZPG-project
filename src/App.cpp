//Include GLFW
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

#include "../include/Window.h"
#include "../include/Scene.h"
#include "../include/Shader.h"
#include "../include/App.h"

static void error_callback(int error, const char *description) {
    fputs(description, stderr);
}

void App::key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);

    if (key == GLFW_KEY_A && action == GLFW_PRESS) {
    }
}


void App::window_focus_callback(GLFWwindow *window, int focused) { printf("window_focus_callback \n"); }

void App::window_iconify_callback(GLFWwindow *window, int iconified) { printf("window_iconify_callback \n"); }

void App::window_size_callback(GLFWwindow *window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}

void App::cursor_callback(GLFWwindow *window, double x, double y) { printf("cursor_callback \n"); }

void App::button_callback(GLFWwindow *window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

App::App() {
    window = std::make_shared<Window>();
    glfwSetErrorCallback(error_callback);
    glfwSetKeyCallback(window->getWindow(), key_callback);
    glfwSetCursorPosCallback(window->getWindow(), cursor_callback);


    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();
}

int App::init() {
    //inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);


    this->scene = std::make_shared<Scene>(window);

    scene->render();

    return 0;
}

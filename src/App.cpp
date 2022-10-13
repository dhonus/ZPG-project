#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../include/Window.h"
#include "../include/Scene.h"
#include "../include/App.h"

App::App() {
    window = std::make_shared<Window>(this->width, this->height);
    glewExperimental = GL_TRUE;
    glewInit();
}

int App::init() {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
                   GLFW_OPENGL_CORE_PROFILE);

    this->scene = std::make_shared<Scene>(window, this->width, this->height);

    scene->render();

    return 0;
}

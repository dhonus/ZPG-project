#include "../include/Window.h"


Window::Window(int width, int height) {
    glfwGetVersion(&major, &minor, &revision);
    printf("Using GLFW %i.%i.%i\n", major, minor, revision);

    glViewport(0, 0, width, height);

    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);

    glfwGetFramebufferSize(this->window, &width, &height);
    if (!this->window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    get_version_info();
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::get_version_info() {
    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
    printf("Vendor %s\n", glGetString(GL_VENDOR));
    printf("Scene %s\n", glGetString(GL_RENDERER));
    printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

GLFWwindow *Window::getWindow() {
    return this->window;
}


#include "../include/Window.h"


Window::Window(int width, int height) {
    glfwGetVersion(&major, &minor, &revision);
    std::cout << "Using GLFW " << major << " " << minor << " " <<  revision << "\n" << std::flush;

    glViewport(0, 0, width, height);

    if (!glfwInit()) {
        std::cout << "ERROR: could not start GLFW3\n" << std::flush;
        exit(-1);
    }

    this->window = glfwCreateWindow(800, 600, "ZPG", NULL, NULL);
    //this->window = glfwCreateWindow(800, 600, "ZPG", glfwGetPrimaryMonitor(), NULL);

    glfwGetFramebufferSize(this->window, &width, &height);
    if (!this->window) {
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(this->window);
    glfwSwapInterval(1);
    get_version_info();
    glfwSetInputMode(this->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Window::get_version_info() {
    std::cout
        << "OpenGL Version: " << glGetString(GL_VERSION)
        << "\nUsing GLEW: " << glewGetString(GLEW_VERSION)
        << "\nVendor: " << glGetString(GL_VENDOR)
        << "\nScene: " << glGetString(GL_RENDERER)
        << "\nGLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n" << std::flush;
}

Window::~Window() {
    glfwDestroyWindow(this->window);
    glfwTerminate();
}

GLFWwindow* Window::getWindow() {
    return this->window;
}


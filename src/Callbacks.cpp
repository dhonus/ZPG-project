//
// Created by daniel on 12.10.22.
//

#include "../include/Callbacks.h"

Camera *Callbacks::camera = nullptr;
Scene *Callbacks::scene = nullptr;
Callbacks *Callbacks::callbacks = nullptr;

float Callbacks::width = 0;
float Callbacks::height = 0;

static auto errorCallback = [](int error, const char *description) {
    std::cout << description << std::flush;
    exit(-1);
};

void Callbacks::init() {

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    auto windowFocusedCallback = [](GLFWwindow *window, int focused) {
        std::cout << "[!!] windowFocusedCallback\n";
    };

    auto windowIconifiedCallback = [](GLFWwindow *window, int iconified) {
        std::cout << "[!!] windowIconifiedCallback\n";
    };

    auto windowSizeChangeCallback = [](GLFWwindow *window, int width, int height) {
        std::cout << "[!!] Resize W: " << width << " H: " << height << "\n" << std::flush;
        glViewport(0, 0, width, height);
        instance().width = width;
        instance().height = height;
        camera->update(instance());
    };

    auto mouseCallback = [](GLFWwindow *win, double x, double y) {
        if (!camera) {
            std::cout << "[!!] Camera not bound\n" << std::flush;
            return;
        }
        camera->mouse(x, y);
    };

    auto keyboard = [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GL_TRUE);
    };

    auto mouseClickCallback = [](GLFWwindow *window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
            GLbyte color[4];
            GLfloat depth;
            GLuint index;

            int width;
            int height;
            glfwGetWindowSize(window, &width, &height);
            GLint x = (GLint) width / 2;
            GLint y = (GLint) height / 2;

            glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
            glReadPixels(x, y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
            glReadPixels(x, y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

            glm::vec3 screenX = glm::vec3(x, y, depth);
            glm::mat4 view = camera->getCamera();
            glm::mat4 projection = camera->getPerspective();
            glm::vec3 pos = glm::unProject(screenX, view, projection, glm::vec4{0, 0, width, height});
            std::cout << "[??] Mouse clicked at " << pos.x << pos.y << pos.z << std::endl;
            instance().clickedPosition = pos;
            instance().clickedId = index;

            instance().notify();
        }
    };

    glfwSetErrorCallback(errorCallback);
    glfwSetKeyCallback(window, keyboard);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetMouseButtonCallback(window, mouseClickCallback);
    glfwSetWindowSizeCallback(window, windowSizeChangeCallback);
    glfwSetWindowIconifyCallback(window, windowIconifiedCallback);
    glfwSetWindowFocusCallback(window, windowFocusedCallback);
}

Callbacks::Callbacks(GLFWwindow &window) {
    this->window = &window;
    this->init();
    this->callbacks = this;
}

void Callbacks::setCamera(Camera *&t_camera) {
    Callbacks::camera = t_camera;
}

void Callbacks::setScene(Scene *&t_scene) {
    Callbacks::scene = t_scene;
}

Callbacks &Callbacks::instance() {
    return *callbacks;
}

//
// Created by daniel on 12.10.22.
//

#ifndef ZPG_CALLBACKS_H
#define ZPG_CALLBACKS_H
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
#include "iostream"
#include "Camera.h"
#include "memory"
#include "Observer.h"
class Camera;
class Callbacks : Observable{
public:
    Callbacks(GLFWwindow* window);
    static void setCamera(std::shared_ptr<Camera> camera);
    static std::shared_ptr<Camera> camera;
private:
    GLFWwindow* window;
    void init();
    static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

    void window_focus_callback(GLFWwindow *window, int focused);

    void window_iconify_callback(GLFWwindow *window, int iconified);

    static void window_size_callback(GLFWwindow *window, int width, int height);

    static void cursor_callback(GLFWwindow *window, double x, double y);

    static void button_callback(GLFWwindow *window, int button, int action, int mode);

    static bool A;
    static bool B;
};


#endif //ZPG_CALLBACKS_H

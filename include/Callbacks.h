//
// Created by daniel on 12.10.22.
//

#ifndef ZPG_CALLBACKS_H
#define ZPG_CALLBACKS_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "iostream"
#include "Camera.h"
#include "memory"
#include "Observer.h"

class Camera;

class Callbacks : public Subject {
public:
    Callbacks(GLFWwindow& window);
    static void setCamera(Camera *&camera);
    static float width, height;
private:
    static Camera* camera;
    static Callbacks* callbacks;
    static Callbacks& instance();
    GLFWwindow* window;
    void init();
};


#endif //ZPG_CALLBACKS_H

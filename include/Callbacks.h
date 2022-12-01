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
#include "Scene.h"

class Camera;
class Scene;

class Callbacks : public Subject {
public:
    Callbacks(GLFWwindow& window);
    static void setCamera(Camera *&t_camera);
    static void setScene(Scene *&t_scene);
    static float width, height;
    glm::vec3 clickedPosition;
    int clickedId;
private:
    static Camera* camera;
    static Scene* scene;
    static Callbacks* callbacks;
    static Callbacks& instance();
    GLFWwindow* window;
    void init();
};


#endif //ZPG_CALLBACKS_H

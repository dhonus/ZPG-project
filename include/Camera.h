//
// Created by daniel on 10/10/22.
//

#ifndef ZPG_CAMERA_H
#define ZPG_CAMERA_H


#include <glm/ext/matrix_float4x4.hpp>
#include <iostream>
#include "memory"
#include "Shader.h"
#include "Observer.h"
#include "Callbacks.h"
#include "Window.h"

class Shader;
class Subject;
class Callbacks;

class Camera : public Observer {
private:
    glm::mat4 camera;
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 upwards;
    Callbacks* callback;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Window> window;
    bool first = true;
    float cameraSpeed = 0.03f;
    float width = 800;
    float height = 600;
    float lastX =  800.0f / 2.0;
    float lastY =  600.0 / 2.0;
    float yaw = -90.0f;
    float pitch = 0.0f;
    float deltaTime = 0.0f;	// Time between current frame and last frame
    float lastFrame = 0.0f; // Time of last frame
public:
    Camera(int width, int height, Callbacks& callback, std::shared_ptr<Window> window);
    glm::mat4 getCamera();
    glm::vec3 getPosition() const;
    glm::mat4 getPerspective();
    void move(bool front, bool back, bool left, bool right, bool up, bool down);
    void mouse(float x, float y);
    void update(Subject& subject);
};


#endif //ZPG_CAMERA_H

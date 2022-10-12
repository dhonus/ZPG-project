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

class Shader;
class Camera : Observer{
private:
    glm::mat4 camera;
    glm::vec3 position{0.0f, -4.0f, -1.0f};
    glm::vec3 target{0.f, 0.f, 1.f};
    glm::vec3 upwards {0.f, 1.f, 0.f};
    bool first = true;
    const float cameraSpeed = 0.03f;
public:
    Camera(int width, int height);
    glm::mat4 getCamera();
    std::shared_ptr<Shader> shader;
    void move(bool front, bool back, bool left, bool right);
    void mouse(float x, float y);
    void update(Observable&);
    float lastX, lastY;
    float yaw, pitch;
};


#endif //ZPG_CAMERA_H

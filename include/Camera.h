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
    glm::vec3 position{0.0f, -2.5f, -1.0f};
    glm::vec3 target{0.f, 3.f, 1.f};
    glm::vec3 upwards {0.f, 1.f, 0.f};
public:
    glm::mat4 getCamera();
    std::shared_ptr<Shader> shader;
    void mouse(double x, double y);
    void update(Observable&);
};


#endif //ZPG_CAMERA_H

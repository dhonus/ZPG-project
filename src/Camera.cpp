//
// Created by daniel on 10/10/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Camera.h"

glm::mat4 Camera::getCamera() {
    return glm::lookAt(this->position, position + target, upwards);
}

void Camera::mouse(double x, double y) {
    this->target.x = sin(glm::radians(x))*cos(glm::radians(x));
    //this->target.y = cos(1);
    std::cout << "Mouse!! X:"<<x<<" Y:"<<y<<"\n";
}

void Camera::update(Observable &) {
    std::cout << "updated camera";
}

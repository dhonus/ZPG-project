//
// Created by daniel on 10/10/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Camera.h"

glm::mat4 Camera::getCamera() {
    return glm::lookAt(this->position, position + target, upwards);
}

void Camera::mouse(float x, float y) {
    if (first) // initially set to true
    {
        lastX = x/2;
        lastY = y/2;
        first = false;
    }

    float xoffset = x - lastX;
    float yoffset = lastY - y; // reversed since y-coordinates range from bottom to top
    lastX = x;
    lastY = y;

    const float sensitivity = 0.5f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;
    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch =  89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;


    /*
     * The pitch is the angle that depicts how much we're looking up or down as seen in the first image. The second image shows the yaw value which represents the magnitude we're looking to the left or to the right. The roll represents how much we roll as mostly used in space-flight cameras. Each of the Euler angles are represented by a single value and with the combination of all 3 of them we can calculate any rotation vector in 3D.
    */


    this->target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target.y = sin(glm::radians(pitch));
    this->target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));


    //this->target.y = cos(1);
    std::cout << "Mouse!! X:"<<x<<" Y:"<<lastX<<"\n";
}

void Camera::update(Observable &) {
    std::cout << "updated camera";
}

Camera::Camera(int width, int height) {
    lastX = width/2,
    lastY = height/2;
}

void Camera::move(bool front, bool back, bool left, bool right) {
    std::cout << "moving " << front<<back<<left<<right<<"\n";
    if (front)
        position += cameraSpeed*target;
    if (back)
        position -= cameraSpeed*target;
    if(left)
        position -= glm::normalize(glm::cross(target, upwards)) * cameraSpeed;
    if(right)
        position += glm::normalize(glm::cross(target, upwards)) * cameraSpeed;
}

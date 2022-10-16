//
// Created by daniel on 10/10/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Camera.h"

glm::mat4 Camera::getCamera() {
    return glm::lookAt(this->position, position + target, upwards);
}

glm::vec3 Camera::getPosition() const{
    return this->position;
}

void Camera::mouse(float x, float y) {
    /*
     * The pitch is the angle that depicts how much we're looking up or down as seen in the first image.
     * The second image shows the yaw value which represents the magnitude we're looking to the left or to the right.
     * The roll represents how much we roll as mostly used in space-flight cameras. Each of the Euler angles are
     * represented by a single value and with the combination of all 3 of them we can calculate any rotation vector in 3D.
    */
    if (first)
    {
        lastX = x;
        lastY = y;
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

    this->target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target.y = sin(glm::radians(pitch));
    this->target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target = glm::normalize(target);
}

void Camera::update(Subject& subject) {
    if (&subject == callback){
        this->width = callback->width;
        this->height = callback->height;
        this->camera = glm::perspective(glm::radians(45.0f), this->width / this->height, 0.1f, 300.0f);
    }
}

Camera::Camera(int width, int height, Callbacks& callback, std::shared_ptr<Window> window) {
    this->position = glm::vec3 {0.0f, 0.0f, 3.0f};
    this->target = glm::vec3 {0.f, 0.f, -2.f};
    this->upwards = glm::vec3 {0.f, 1.f, 0.f};
    this->lastX = width/2,
    this->lastY = height/2;
    this->callback = &callback;
    this->window = window;
    this->width = width;
    this->height = height;
    this->camera = glm::perspective(glm::radians(45.0f), this->width / this->height, 0.1f, 300.0f);
    this->target.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target.y = sin(glm::radians(pitch));
    this->target.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    this->target = glm::normalize(target);
}

void Camera::move(bool front, bool back, bool left, bool right, bool up, bool down) {
    float currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;
    this->cameraSpeed = 3.5 * this->deltaTime;

    if (front)
        position += cameraSpeed*target;
    if (back)
        position -= cameraSpeed*target;
    if (left)
        position -= glm::normalize(glm::cross(target, upwards)) * cameraSpeed;
    if (right)
        position += glm::normalize(glm::cross(target, upwards)) * cameraSpeed;
    if (up)
        position += cameraSpeed*upwards;
    if (down)
        position -= cameraSpeed*upwards;
}

glm::mat4 Camera::getPerspective() {
    return this->camera;
}

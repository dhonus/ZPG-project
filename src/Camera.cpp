//
// Created by daniel on 10/10/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Camera.h"
/// compute view matrix
glm::mat4 Camera::getCamera() {
    auto target_pos = position + target;
    return glm::lookAt(this->position, target_pos, upwards);
}

glm::vec3 Camera::getPosition() const{
    return this->position;
}

glm::vec3 Camera::getDirection() const {
    return this->target;
}

void Camera::mouse(float x, float y) {
    if (first)
    {
        this->lastX = x;
        this->lastY = y;
        this->first = false;
    }
    glm::vec2 camera_offset_since_last_frame = glm::vec2(x - lastX, lastY - y); // y val reversed since y-coordinates range from bottom to top
    this->lastX = x;
    this->lastY = y;

    auto sensitivity = 0.20f;
    camera_offset_since_last_frame.x *= sensitivity;
    camera_offset_since_last_frame.y *= sensitivity;
    sideways_angle += camera_offset_since_last_frame.x;
    up_down_angle += camera_offset_since_last_frame.y;

    if(up_down_angle > 89.0f)
        up_down_angle =  89.0f;
    if(up_down_angle < -89.0f)
        up_down_angle = -89.0f;

    // get the rotation vector
    this->target.x = cos(glm::radians(sideways_angle)) * cos(glm::radians(up_down_angle));
    this->target.y = sin(glm::radians(up_down_angle));
    this->target.z = sin(glm::radians(sideways_angle)) * cos(glm::radians(up_down_angle));
    this->target = glm::normalize(target);

    notify();
}

void Camera::update(Subject& subject) {
    if (&subject == callback){
        this->width = callback->width;
        this->height = callback->height;
        // projection matrix
        this->camera = glm::perspective(glm::radians(fov), this->width / this->height, 0.1f, 300.0f);
        notify();
    }
}

Camera::Camera(int width, int height, Callbacks& callback) {
    this->callback = &callback;
    this->position = glm::vec3 {90.0f, 20.0f, 40.0f};
    this->target = glm::vec3 {0.f, 0.f, -2.f};
    this->upwards = glm::vec3 {0.f, 1.f, 0.f};
    this->width = width;
    this->height = height;
    this->fov = 60.0f;
    // projection matrix
    this->camera = glm::perspective(glm::radians(fov), this->width / this->height, 0.1f, 300.0f);

    notify();
}

void Camera::move(bool front, bool back, bool left, bool right, bool up, bool down) {
    float currentFrame = glfwGetTime();
    this->deltaTime = currentFrame - this->lastFrame;
    this->lastFrame = currentFrame;
    this->cameraSpeed = 15 * this->deltaTime;

    auto orig_pos = position;
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

    if (position != orig_pos){
        notify();
    }
}

/// get projection matrix
glm::mat4 Camera::getPerspective() {
    return this->camera;
}

void Camera::setShader(Shader* t_shader){
    this->shader = t_shader;
    attach(this->shader);
}

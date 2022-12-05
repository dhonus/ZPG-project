//
// Created by daniel on 10/8/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Trans.h"
#include <glm/gtx/string_cast.hpp>

Trans::Trans() {}

TransRotate::TransRotate(float speed, glm::vec3 position, glm::vec3 axis) {
    this->speed = speed;
    this->position = position;
    this->axis = axis;
}

TransRotate::TransRotate(bool stationary, float speed, glm::vec3 position, glm::vec3 axis) {
    this->speed = speed;
    this->position = position;
    this->axis = axis;
    this->stationary = stationary;
}

glm::mat4 TransRotate::transform() {
    glm::mat4 trans = glm::mat4(1.0f);
    if (stationary) {
        trans = glm::rotate(glm::mat4(1.0f), speed, axis);
    } else {
        trans = glm::rotate(trans, (float) glfwGetTime() * speed, glm::normalize(axis));
    }
    trans = glm::translate(trans, position);
    return trans;
}

TransScale::TransScale(float factor) {
    this->factor = factor;
}

glm::mat4 TransScale::transform() {
    return glm::scale(glm::mat4{1.0f}, glm::vec3{factor});
}

TransMove::TransMove(glm::vec3 moveDirection) {
    this->moveDirection = moveDirection;
}

glm::mat4 TransMove::transform() {
    glm::mat4 mod{1.0f};
    glm::rotate(mod, glm::radians(1.0f), moveDirection);
    mod = glm::translate(mod, moveDirection);

    return mod;
}

glm::mat4 Trans::transform() {
    // for each element in transformations, call the transform member function
    glm::mat4 mod{1.0f};
    for (auto &trans: transformations) {
        mod *= trans->transform();
    }
    return mod;
}

Composite *Trans::add(std::shared_ptr<Composite> transformation) {
    transformations.push_back(transformation);
    return this;
}

void Trans::remove(std::shared_ptr<Composite> g) {
    transformations.remove(g);
}

Trans::~Trans() {
    transformations.clear();
}

glm::mat4 Trans::getMatrix() {
    return transform();
}

TransParMove::TransParMove(glm::mat4 B, float speed) {
    this->A = glm::mat4(
            glm::vec4(-1.0, 3.0, -3.0, 1.0),
            glm::vec4(3.0, -6.0, 3.0, 0),
            glm::vec4(-3.0, 3.0, 0, 0),
            glm::vec4(1, 0, 0, 0)),
            this->B = B;
    this->speed = speed;
}

glm::mat4 TransParMove::transform() {
    if (t >= 1.0f || t <= 0.0f)
        delta *= -1;
    t += delta * speed;

    glm::vec4 moveDirection{1.0f, 1.0f, 1.0f, 0.0f};
    glm::mat4 mod{1.0f};
    glm::vec4 p = glm::vec4(pow(t, 3), pow(t, 2), t, 1.0f);
    // p * A -> bázové polynomy
    moveDirection = moveDirection * (p * A * glm::transpose(B));
    mod = glm::translate(mod, glm::vec3(moveDirection));
    return mod;
}


//
// Created by daniel on 10/8/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Trans.h"

Trans::Trans() {}

TransRotate::TransRotate(float speed, glm::vec3 position, glm::vec3 axis){
    this->speed = speed;
    this->position = position;
    this->axis = axis;
}
TransRotate::TransRotate(bool stationary, float speed, glm::vec3 position, glm::vec3 axis){
    this->speed = speed;
    this->position = position;
    this->axis = axis;
    this->stationary = stationary;
}

glm::mat4 TransRotate::transform() const {
    glm::mat4 trans = glm::mat4(1.0f);
    if (stationary){
        trans = glm::rotate(trans, glm::radians(90.0f), axis);
    } else {
        trans = glm::rotate(trans, (float)glfwGetTime() * speed, axis);
    }
    trans = glm::translate(trans, position);
    return trans;
}

TransScale::TransScale(float factor){
    this->factor = factor;
}

glm::mat4 TransScale::transform() const {
    return glm :: scale (glm::mat4{1.0f} , glm::vec3{factor});
}

TransMove::TransMove(glm::vec3 moveDirection){
    this->moveDirection = moveDirection;
}

glm::mat4 TransMove::transform() const {
    glm::mat4 mod {1.0f};
    glm::rotate(mod, glm::radians(1.0f), moveDirection);
    mod = glm::translate(mod, moveDirection);
    return mod;
}

glm::mat4 Trans::transform() const {
    // for each element in transformations, call the transform member function
    glm::mat4 mod {1.0f};
    for (auto& trans : transformations){
        mod *= trans->transform();
    }
    return mod;
}

Composite* Trans::add(std::shared_ptr<Composite> transformation) {
    transformations.push_back(transformation);
    return this;
}

void Trans::remove(std::shared_ptr<Composite> g){
    transformations.remove(g);
}

Trans::~Trans(){}


glm::mat4 Trans::getMatrix(){
    return transform();
}

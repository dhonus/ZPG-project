//
// Created by daniel on 10/30/22.
//

#include "../include/Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    this->color = color;
    this->position = position;
}

int Light::getType() const {
    return type;
}

const glm::vec3 &Light::getPosition() const {
    return position;
}

const glm::vec3 &Light::getDirection() const {
    return direction;
}

const glm::vec3 &Light::getColor() const {
    return color;
}

float Light::getCutoff() const {
    return cutoff;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    type = 1;
    this->color = color;
    this->position = position;
}

DirLight::DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction) : Light(position, color) {
    type = 2;
    this->color = color;
    this->position = position;
    this->direction = direction;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutoff) : Light(position, color) {
    type = 3;
    this->cutoff = cutoff;
    this->color = color;
    this->position = position;
    this->direction = direction;
}

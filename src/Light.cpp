//
// Created by daniel on 10/30/22.
//

#include "../include/Light.h"

Light::Light(glm::vec3 position, glm::vec3 color) {
    pColor = color;
    pPosition = position;
}

glm::vec3 Light::getPosition() {
    return pPosition;
}

glm::vec3 Light::getColor() {
    return pColor;
}

PointLight::PointLight(glm::vec3 position, glm::vec3 color) : Light(position, color) {
    pType = 1;
    pColor = color;
    pPosition = position;
}

DirLight::DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction) : Light(position, color) {
    pType = 2;
    pColor = color;
    pPosition = position;
    pDirection = direction;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutoff) : Light(position, color) {
    pType = 3;
    pCutoff = cutoff;
    pColor = color;
    pPosition = position;
    pDirection = direction;
}

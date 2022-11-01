//
// Created by daniel on 10/30/22.
//

#include "../include/Light.h"

Light::Light(glm::vec3 t_position, glm::vec3 t_color) {
    color = t_color;
    position = t_position;
}

glm::vec3 Light::getPosition() {
    return position;
}

glm::vec3 Light::getColor() {
    return color;
}

Light::Light() {

}

AnotherLight::AnotherLight(glm::vec3 t_position, glm::vec3 t_color) : Light(t_position, t_color) {
    color = t_color;
    position = t_position;
}

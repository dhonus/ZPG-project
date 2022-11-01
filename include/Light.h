//
// Created by daniel on 10/30/22.
//

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/vec3.hpp>


class Light {
public:
    Light(glm::vec3 t_position, glm::vec3 t_color);
    Light();
    glm::vec3 getPosition();
    glm::vec3 getColor();
    int type;
    glm::vec3 position;
    glm::vec3 color;
    glm::vec3 direction;

    float constant;
    float linear;
    float quadratic;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class AnotherLight : public Light{
    int a = 10;
public:
    AnotherLight(glm::vec3 t_position, glm::vec3 t_color);
};


#endif //ZPG_LIGHT_H

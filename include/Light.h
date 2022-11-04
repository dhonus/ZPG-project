//
// Created by daniel on 10/30/22.
//

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/vec3.hpp>


class Light {
public:
    Light(glm::vec3 position, glm::vec3 color);
    glm::vec3 getPosition();
    glm::vec3 getColor();
    int pType;
    glm::vec3 pPosition;
    glm::vec3 pColor;
    glm::vec3 pDirection;

    float constant;
    float linear;
    float quadratic;
    float pCutoff;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

class PointLight : public Light{
public:
    PointLight(glm::vec3 position, glm::vec3 color);
};

class DirLight : public Light{
public:
    DirLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction);
};

class SpotLight : public Light{
public:
    SpotLight(glm::vec3 position, glm::vec3 color, glm::vec3 direction, float cutoff);
};


#endif //ZPG_LIGHT_H

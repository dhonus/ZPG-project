//
// Created by daniel on 10/30/22.
//

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/vec3.hpp>


class Light {
public:
    Light(glm::vec3 position, glm::vec3 color);
    [[nodiscard]] int getType() const;
    [[nodiscard]] const glm::vec3 &getPosition() const;
    [[nodiscard]] const glm::vec3 &getDirection() const;
    [[nodiscard]] const glm::vec3 &getColor() const;
    [[nodiscard]] float getCutoff() const;

protected:
    int type;
    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 direction;
    float cutoff;
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

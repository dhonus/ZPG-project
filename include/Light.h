//
// Created by daniel on 10/30/22.
//

#ifndef ZPG_LIGHT_H
#define ZPG_LIGHT_H

#include <glm/vec3.hpp>

class Light {
private:
    glm::vec3 position;
    glm::vec3 color;
public:
    Light(glm::vec3 t_position, glm::vec3 t_color);
    glm::vec3 getPosition();
    glm::vec3 getColor();
};


#endif //ZPG_LIGHT_H

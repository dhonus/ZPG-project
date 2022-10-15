//
// Created by daniel on 10/8/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Trans.h"

Trans::Trans() {
    this->current = glm::mat4(1.0f);
}

glm::mat4 Trans::getMatrix(){
    this->current*=transform();
    return current;
}

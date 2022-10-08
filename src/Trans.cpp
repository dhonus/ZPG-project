//
// Created by daniel on 10/8/22.
//

#include <glm/ext/matrix_transform.hpp>
#include "../include/Trans.h"
#include "iostream"

Trans::Trans() {
    this->current = glm::mat4(1.0f);
}

glm::mat4 Trans::getMatrix(){
    return this->current;
}

// these methods will be replaced with more relevant operations as needed
// currently unnecessary to do so
void Trans::scale(){
    int rot = 1;
    this->current = glm :: scale ( this->current , glm :: vec3 (rot * 0.999f ));
}

void Trans::move(){
    this->current = glm :: scale ( this->current , glm :: vec3 (1.001f ));
}

void Trans::rotate(float deg, float quantifier){
    this->current = glm::rotate(this->current,glm::radians(deg), glm::vec3(0.0f, 0.0f, quantifier*1.0f));
}

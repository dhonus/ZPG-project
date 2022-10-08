//
// Created by daniel on 10/8/22.
//

#include <iostream>
#include "../include/Model.h"

Model::Model(std::vector<float> b) {
    this->VBO = std::make_shared<Vbo>(b);
    this->VAO = std::make_shared<Vao>(VBO);
    this->VAO->bind_vertex_array();
}

int Model::draw(){
    glDrawArrays(GL_POLYGON, 0, 4);
    return 0;
}
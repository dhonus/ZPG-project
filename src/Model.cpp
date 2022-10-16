//
// Created by daniel on 10/8/22.
//

#include <iostream>
#include "../include/Model.h"

Model::Model(const std::vector<float> &vertices, GLenum mode, int vertexCount, int posSize, int colSize, int colOffset, int genSize) {
    this->VBO = std::make_shared<Vbo>(vertices, posSize, colSize, colOffset, genSize);
    this->VAO = std::make_shared<Vao>(VBO);
    this->VAO->bind_vertex_array();
    this->mode = mode;
    this->vertexCount = vertexCount;
}

int Model::draw(){
    this->VAO->bind_vertex_array();
    glDrawArrays(mode, 0, vertexCount);
    return 0;
}
//
// Created by daniel on 10/8/22.
//

#include <iostream>
#include "../include/Model.h"


Model::Model(const std::vector<float> &vertices, GLenum mode, int vertexCount, int positionSize, int normalsSize,
             int normalsOffset, int overallSize) {
    this->mesh = std::make_shared<Mesh>(vertices, mode, vertexCount, positionSize, normalsSize, normalsOffset,
                                        overallSize);
}

int Model::draw() {
    this->mesh->bind_vertex_array();
    //this->VAO->bind_vertex_array();
    this->mesh->draw_arrays();
    return 0;
}

Model::Model(const std::string fileName) {
    this->mesh = std::make_shared<Mesh>(fileName);
    std::cout << "\t[->] Created model from file: " << fileName << std::endl;
}

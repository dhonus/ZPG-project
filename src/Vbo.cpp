#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../include/Vbo.h"
#include "iostream"
Vbo::Vbo(std::vector<float> &t_points, int posSize, int colSize, int colOffset, int genSize) {
    this->points = t_points;
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t_points.size() * sizeof(float), t_points.data(), GL_STATIC_DRAW);
    this->posSize = posSize;
    this->colSize = colSize;
    this->colOffset = colOffset;
    this->genSize = genSize;
}

Vbo::Vbo(){
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
}

void Vbo::bind_buffer() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), this->points.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, posSize, GL_FLOAT, GL_FALSE, genSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, colSize, GL_FLOAT, GL_FALSE, genSize * sizeof(float), (void*)(colOffset * sizeof(float)));
    glEnableVertexAttribArray(1);
}

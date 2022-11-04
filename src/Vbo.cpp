#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../include/Vbo.h"
#include "iostream"
Vbo::Vbo(const std::vector<float> &t_points, int positionSize, int normalsSize, int normalsOffset, int overallSize) {
    this->points = t_points;
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t_points.size() * sizeof(float), t_points.data(), GL_STATIC_DRAW);
    this->positionSize = positionSize;
    this->normalsSize = normalsSize;
    this->normalsOffset = normalsOffset;
    this->overallSize = overallSize;
}

Vbo::Vbo(){
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
}

void Vbo::bind_buffer() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, this->points.size() * sizeof(float), this->points.data(), GL_STATIC_DRAW);

    // pPosition
    glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, overallSize * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normals
    glVertexAttribPointer(1, normalsSize, GL_FLOAT, GL_FALSE, overallSize * sizeof(float), (void*)(normalsOffset * sizeof(float)));
    glEnableVertexAttribArray(1);
}

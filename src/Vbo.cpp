#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../include/Vbo.h"

Vbo::Vbo(std::vector<float> t_points) {
    this->points = t_points;
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t_points.size() * sizeof(float), t_points.data(), GL_STATIC_DRAW);
}

Vbo::Vbo(){
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
}

void Vbo::bind_buffer() {
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, 2* sizeof(this->points)  * sizeof(float), this->points.data(), GL_STATIC_DRAW);

    // position
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

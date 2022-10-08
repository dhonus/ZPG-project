#include "../include/Vao.h"
#include "iostream"
Vao::Vao(std::shared_ptr<Vbo> vbo) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    std::cout << this->VAO;
    vbo->bind_buffer();
}

void Vao::bind_vertex_array() {
    glBindVertexArray(VAO);
}

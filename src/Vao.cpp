#include "../include/Vao.h"
#include "iostream"

Vao::Vao(std::shared_ptr<Vbo> vbo) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    vbo->bind_buffer();
}

Vao::Vao(std::shared_ptr<Vbo> vbo, bool object) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    vbo->bind_buffer(object);
}

void Vao::bind_vertex_array() {
    glBindVertexArray(VAO);
}

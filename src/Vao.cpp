#include "../include/Vao.h"

Vao::Vao(Vbo *vbo) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO

    vbo->bind_buffer();
}

void Vao::bind_vertex_array() {
    glBindVertexArray(VAO);
}

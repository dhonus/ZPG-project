#include "../include/Vao.h"

Vao::Vao(Vbo *vbo) {
    VAO = 0;
    glGenVertexArrays(1, &VAO); //generate the VAO
    glBindVertexArray(VAO); //bind the VAO
    glEnableVertexAttribArray(0); //enable vertex attributes

    vbo->bind_buffer();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
}

void Vao::bind_vertex_array() {
    glBindVertexArray(VAO);
}

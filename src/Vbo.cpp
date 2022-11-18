#include "../include/Vbo.h"

Vbo::Vbo(const std::vector<float> &t_points, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize) {
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

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    // pPosition
    glVertexAttribPointer(0, positionSize, GL_FLOAT, GL_FALSE, overallSize * sizeof(float), (void*)0);
    // normals
    glVertexAttribPointer(1, normalsSize, GL_FLOAT, GL_FALSE, overallSize * sizeof(float), (void*)(normalsOffset * sizeof(float)));

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, overallSize * sizeof(float), (void*)(overallSize - 2 * sizeof(float)));
}

// assimp

Vbo::Vbo(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int vertexCount){
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

    glBindVertexArray(0);
}

Vbo::Vbo(aiMesh* mesh, Vertex* pVertices, unsigned int* pIndices){
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->mNumVertices, pVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(8 * sizeof(GLfloat)));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh->mNumFaces * 3, pIndices, GL_STATIC_DRAW);

}

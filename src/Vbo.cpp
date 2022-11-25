#include "../include/Vbo.h"

Vbo::Vbo(const std::vector<float> &t_points, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize) {
    this->points = t_points;
    VBO = 0;
    glGenBuffers(1, &VBO); // generate the VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, t_points.size() * sizeof(float), &t_points[0], GL_STATIC_DRAW);
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

void Vbo::bind_buffer(bool object) {
    std::cout << "obk" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, points.size()*sizeof(float), &points[0], GL_STATIC_DRAW);

    //enable vertex attributes
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (GLvoid*)(sizeof(float) * (overallSize - 2)));
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void *) (8 * sizeof(float)));
}

// assimp


Vbo::Vbo(aiMesh* mesh, std::vector<float> data){
    // pass
}

Vbo::Vbo(const std::vector<Vertex> &vertices, const std::vector<unsigned int> &indices, int vertexCount) {

}

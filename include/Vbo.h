//
// Created by daniel on 27.9.22.
//

#ifndef OGL_TST_02_VBO_H
#define OGL_TST_02_VBO_H

#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec4.hpp>

#include <glm/ext/matrix_float4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../include/Mesh.h"
#include "iostream"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

struct Vertex;

class Vbo {
private:
    GLuint VBO;
    GLuint EBO;
    std::vector<float> points;
    int positionSize;
    int normalsSize;
    int normalsOffset;
    int overallSize;
    int vertexCount;
public:
    Vbo(const std::vector<float> &t_points, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize);
    Vbo();
    Vbo(std::vector<Vertex> vertices, std::vector<unsigned int> indices, int vertexCount);
    Vbo(aiMesh* mesh, std::vector<float> data);
    void bind_buffer();
};


#endif //OGL_TST_02_VBO_H

//
// Created by daniel on 11/16/22.
//

#ifndef ZPG_MESH_H
#define ZPG_MESH_H
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <string>
#include <glm/vec4.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "Vbo.h"
#include "Vao.h"
#include <memory>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 tangent;
};
struct TextureStruct {
    unsigned int id;
    std::string type;
};

class Vbo;
class Vao;

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<uint> indices;
    std::vector<TextureStruct> textures;
    Mesh(std::vector<Vertex> vertices, std::vector<uint> indices, std::vector<TextureStruct> textures);
    Mesh(const std::vector<float> &vertices, GLenum mode, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize);
    Mesh(const std::string& fileName);

    void draw_arrays();
    void bind_vertex_array();
private:
    std::shared_ptr<Vbo> VBO;
    std::shared_ptr<Vao> VAO;
    GLenum mode;
    int vertexCount;

    std::vector<float> data;
    int count = 0;
};


#endif //ZPG_MESH_H

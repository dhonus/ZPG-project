//
// Created by daniel on 11/16/22.
//

#include "../include/Mesh.h"
int indicesCount = 0;

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures){
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    this->VBO = std::make_shared<Vbo>(vertices, indices, vertexCount);
    this->VAO = std::make_shared<Vao>(VBO);

    setup();
}

Mesh::Mesh(const std::vector<float> &vertices, GLenum mode, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize){
    this->mode = mode;
    this->vertexCount = vertexCount;

    this->VBO = std::make_shared<Vbo>(vertices, vertexCount, positionSize, normalsSize, normalsOffset, overallSize);
    this->VAO = std::make_shared<Vao>(VBO);
    bind_vertex_array();
}

void Mesh::setup() {

}

void Mesh::bind_vertex_array() {
    this->VAO->bind_vertex_array();
}

void Mesh::draw_arrays(){
    glDrawArrays(mode, 0, vertexCount);
}

Mesh::Mesh(const std::string& fileName) {
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
                                 | aiProcess_OptimizeMeshes              // sloučení malých plošek
                                 | aiProcess_JoinIdenticalVertices       // NUTNÉ jinak hodně duplikuje
                                 | aiProcess_Triangulate                 // prevod vsech ploch na trojuhelniky
                                 | aiProcess_CalcTangentSpace;           // vypocet tangenty, nutny pro spravne pouziti normalove mapy

    //aiProcess_GenNormals/ai_Process_GenSmoothNormals - vypocet normal s jemnych prechodem v pripade, ze objekt neobsahuje normaly

    std::string file = "../models/obj/" + fileName;
    const aiScene* scene = importer.ReadFile("../models/obj/model.obj", importOptions);
    aiMesh* mesh = scene->mMeshes[0];

    this->mode = GL_TRIANGLES;

    if (scene) {
        count = mesh->mNumFaces * 3;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++){
            for (unsigned int j = 0; j < 3; j++)
            {
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mVertices[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].y);
                data.push_back(mesh->mNormals[mesh->mFaces[i].mIndices[j]].z);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].x);
                data.push_back(mesh->mTextureCoords[0][mesh->mFaces[i].mIndices[j]].y);
            }
        }
    }

    indicesCount = mesh->mNumFaces * 3;
    this->vertexCount = count;

    this->VBO = std::make_shared<Vbo>(mesh, data);
    this->VAO = std::make_shared<Vao>(VBO);

    VAO->bind_vertex_array();

    GLuint err = glGetError();
    if (err != GL_NO_ERROR)
    {
        std::cout << "GL ERROR: " << err << std::endl;
        return;
    }


    glBindVertexArray(0);

}

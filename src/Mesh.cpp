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
    const aiScene* scene = importer.ReadFile(file, importOptions);

    if (scene) { //pokud bylo nacteni uspesne
        printf("scene->mNumMeshes = %d\n", scene->mNumMeshes);
        printf("scene->mNumMaterials = %d\n", scene->mNumMaterials);

        for (unsigned int i = 0; i < scene->mNumMaterials; i++)                       //Materials
        {
            const aiMaterial* mat = scene->mMaterials[i];

            aiString name;
            mat->Get(AI_MATKEY_NAME, name);
            printf("Material [%d] name %s\n", i, name.C_Str());

            aiColor4D d;

            glm::vec4 diffuse = glm::vec4(0.8f, 0.8f, 0.8f, 1.0f);
            if (AI_SUCCESS == aiGetMaterialColor(mat, AI_MATKEY_COLOR_DIFFUSE, &d))
                diffuse = glm::vec4(d.r, d.g, d.b, d.a);
        }

        for (unsigned int i = 0; i < scene->mNumMeshes; i++)                      //Objects
        {
            aiMesh* mesh = scene->mMeshes[i];

            Vertex* pVertices = new Vertex[mesh->mNumVertices];
            std::memset(pVertices, 0, sizeof(Vertex) * mesh->mNumVertices);

            for (unsigned int i = 0; i < mesh->mNumVertices; i++)
            {
                if (mesh->HasPositions())
                {
                    pVertices[i].Position.x = mesh->mVertices[i].x;
                    pVertices[i].Position.y = mesh->mVertices[i].y;
                    pVertices[i].Position.z = mesh->mVertices[i].z;
                }
                if (mesh->HasNormals())
                {
                    pVertices[i].Normal.x = mesh->mNormals[i].x;
                    pVertices[i].Normal.y = mesh->mNormals[i].y;
                    pVertices[i].Normal.z = mesh->mNormals[i].z;
                }
                if (mesh->HasTextureCoords(0))
                {
                    pVertices[i].TexCoords.x = mesh->mTextureCoords[0][i].x;
                    pVertices[i].TexCoords.y = mesh->mTextureCoords[0][i].y;
                }
                if (mesh->HasTangentsAndBitangents())
                {
                    pVertices[i].tangent.x = mesh->mTangents[i].x;
                    pVertices[i].tangent.y = mesh->mTangents[i].y;
                    pVertices[i].tangent.z = mesh->mTangents[i].z;
                }
            }

            unsigned int* pIndices = nullptr;

            if (mesh->HasFaces())
            {

                pIndices = new unsigned int[mesh->mNumFaces * 3];
                for (unsigned int i = 0; i < mesh->mNumFaces; i++)
                {
                    pIndices[i * 3] = mesh->mFaces[i].mIndices[0];
                    pIndices[i * 3 + 1] = mesh->mFaces[i].mIndices[1];
                    pIndices[i * 3 + 2] = mesh->mFaces[i].mIndices[2];
                }
            }

            this->VBO = std::make_shared<Vbo>(mesh, pVertices, pIndices);
            this->VAO = std::make_shared<Vao>(VBO);

            VAO->bind_vertex_array();

            GLuint err = glGetError();
            if (err != GL_NO_ERROR)
            {
                std::cout << "GL ERROR: " << err << std::endl;
                return;
            }

            indicesCount = mesh->mNumFaces * 3;
            this->vertexCount = indicesCount;

            delete[] pVertices;
            delete[] pIndices;
        }
    }
    else {
        printf("Error during parsing mesh from %s : %s \n", fileName.c_str(), importer.GetErrorString());
    }
    glBindVertexArray(0);

}

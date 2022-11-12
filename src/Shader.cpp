#include "../include/Shader.h"
#include "vector"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include "../lib/stb_image.h"

Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader,
               Camera *&camera,
               const std::vector<std::shared_ptr<Light>> &lights, bool skybox) {
    this->camera = camera;
    this->camera->setShader(this);
    std::string vs = this->load(vertexShader);
    std::string fs = this->load(fragmentShader);
    this->vertex_shader = vs.c_str();
    this->fragment_shader = fs.c_str();
    this->lights = lights;
    this->skybox = skybox;
    this->compile();
}

std::string Shader::load(const std::string &t_shader){
    std::string filepath = "../shaders/" + t_shader;
    std::string temp{};
    output = "";

    std::ifstream theFile(filepath);

    if(!theFile){
        std::cout << "could not find shader " << filepath << "\n" << std::flush;
        exit(-1);
    }

    while (getline (theFile, temp))
        output += temp + "\n";

    theFile.close();
    return output;
}

GLint Shader::uniformMapper(const std::string &uniformName){
    if (uniforms.find(uniformName) != uniforms.end())
        return uniforms[uniformName];

    uniforms[uniformName] = glGetUniformLocation(shaderProgram, uniformName.c_str());
    std::cout << uniforms[uniformName] <<"\n";
    return uniforms[uniformName];
}

void Shader::compile() {

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertex_shader, NULL);
    glCompileShader(vertexShader);

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, vertexShader);
    glLinkProgram(shaderProgram);

    error_check();

    glProgramUniform1i(shaderProgram, uniformMapper("how_many_lights"), lights.size());
    /* LIGHTS */
    for (size_t i = 0; i < lights.size(); ++i){
        glProgramUniform3fv(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].color"), 1, glm::value_ptr(lights[i]->getColor()));
        glProgramUniform3fv(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].position"), 1, glm::value_ptr(lights[i]->getPosition()));
        glProgramUniform1i(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].type"), lights[i]->pType);
        if (lights[i]->pType == 2 || lights[i]->pType == 3)
            glProgramUniform3fv(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].direction"), 1, glm::value_ptr(lights[i]->pDirection));
        if (lights[i]->pType == 3)
            glProgramUniform1f(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].cutoff"), lights[i]->pCutoff);
    }

    glProgramUniform1f(shaderProgram, uniformMapper("foggy"), fog);
    if (this->skybox){
        std::vector<std::string> faces {
            "right.jpg",
            "left.jpg",
            "top.jpg",
            "bottom.jpg",
            "front.jpg",
            "back.jpg"
        };

        unsigned int textureID;
        glGenTextures(1, &ourTexture);
        glBindTexture(GL_TEXTURE_2D, ourTexture);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        int width, height, nrChannels;
        for (unsigned int i = 0; i < 6; ++i)
        {
            std::string loc = "../textures/nicer_skybox/" + faces[i];
            std::cout << loc << std::endl;
            unsigned char *data = stbi_load(loc.c_str(), &width, &height, &nrChannels, 0);
            if (data)
            {
                glTexImage2D(
                        GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                        0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
                );
                glGenerateMipmap(GL_TEXTURE_2D);
            }
            else
            {
                std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            }
            stbi_image_free(data);
        }
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
    }
    else {
        glGenTextures(1, &ourTexture);
        glBindTexture(GL_TEXTURE_2D, ourTexture);

        // set the ourTexture wrapping/filtering options (on the currently bound ourTexture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // load and generate the ourTexture
        int width, height, nrChannels;
        unsigned char *data = stbi_load("../textures/container.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load ourTexture" << std::endl;
        }
        glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture"), 0);
        stbi_image_free(data);
    }
}

void Shader::draw(glm::mat4 t_matrix, glm::vec3 t_objectColor) {
    glUseProgram(shaderProgram);
    if (this->skybox){
        glDepthMask(GL_FALSE);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ourTexture);
    } else{
        glDepthMask(GL_TRUE);
        glBindTexture(GL_TEXTURE_2D, ourTexture);
    }
    glUniformMatrix4fv(uniformMapper("modelMatrix"), 1, GL_FALSE, &t_matrix[0][0]);
    glUniform3fv(uniformMapper("u_objectColor"), 1, glm::value_ptr(t_objectColor));
    glUniform3fv(uniformMapper("lightPos"), 1, glm::value_ptr(lights[0]->getPosition()));
    glProgramUniform3fv(shaderProgram, uniformMapper("u_lightColor"), 1, glm::value_ptr(lights[0]->getColor()));
    glActiveTexture(GL_TEXTURE0);
}

void Shader::error_check() {
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        std::cout << "linker failure: " << strInfoLog;
        delete[] strInfoLog;
    }
}

void Shader::update(Subject& subject) {
    if(&subject == camera) {
        this->projection = camera->getPerspective();
        this->camMatrix = camera->getCamera();
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camMatrix));
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("cameraDirection"), 1, GL_FALSE, glm::value_ptr(camMatrix));
        glProgramUniform3fv(shaderProgram, uniformMapper("cameraPosition"), 1, glm::value_ptr(camera->getPosition()));
        for (size_t i = 0; i < lights.size(); ++i){
            if (lights[i]->pType == 3){
                glProgramUniform3fv(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].position"), 1, glm::value_ptr(camera->getPosition()));
                glProgramUniform3fv(shaderProgram, uniformMapper("lights[" + std::to_string(i) + "].direction"), 1, glm::value_ptr(camera->getDirection()));
            }
        }
    }
}

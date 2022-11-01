#include "../include/Shader.h"
#include "vector"
#include <iostream>
#include <fstream>
Shader::Shader(const std::string &vertexShader,
               const std::string &fragmentShader,
               Camera *&camera,
               std::shared_ptr<Light> light) {
    this->camera = camera;
    this->camera->setShader(this);
    std::string vs = this->load(vertexShader);
    std::string fs = this->load(fragmentShader);
    this->vertex_shader = vs.c_str();
    this->fragment_shader = fs.c_str();
    this->light = light;
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

    glProgramUniform3fv(shaderProgram, uniformMapper("u_lightColor"), 1, glm::value_ptr(light->getColor()));
    glProgramUniform3fv(shaderProgram, uniformMapper("lightPos"), 1, glm::value_ptr(light->getPosition()));
    glProgramUniform1f(shaderProgram, uniformMapper("foggy"), fog);

    /* LIGHTS */
    glProgramUniform1i(shaderProgram, uniformMapper("how_many_lights"), 2);
    std::unique_ptr<Light> l = std::make_unique<Light>();
    l->color = light->color;
    l->position = light->position;
    glProgramUniform1f(shaderProgram, uniformMapper("lights[0].constant"), 1.0f);

}

void Shader::draw(glm::mat4 t_matrix, glm::vec3 t_objectColor) {
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(uniformMapper("modelMatrix"), 1, GL_FALSE, &t_matrix[0][0]);
    glUniform3fv(uniformMapper("u_objectColor"), 1, glm::value_ptr(t_objectColor));
    glProgramUniform3fv(shaderProgram, uniformMapper("u_lightColor"), 1, glm::value_ptr(light->getColor()));

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
    if(&subject == camera){
        this->projection = camera->getPerspective();
        this->camMatrix = camera->getCamera();
        std::cout << "cam change\n";
        //glProgramUniformMatrix4fv(shader, ...)
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projection));
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("viewMatrix"), 1, GL_FALSE, glm::value_ptr(camMatrix));
        glProgramUniformMatrix4fv(shaderProgram, uniformMapper("cameraDirection"), 1, GL_FALSE, glm::value_ptr(camMatrix));
        glProgramUniform3fv(shaderProgram, uniformMapper("cameraPosition"), 1, glm::value_ptr(camera->getPosition()));
    }
}

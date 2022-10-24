#include "../include/Shader.h"
#include "vector"
#include <iostream>
#include <fstream>
Shader::Shader(const std::string &vertexShader, const std::string &fragmentShader, Camera *&camera) {
    this->camera = camera;
    std::string vs = this->load(vertexShader);
    std::string fs = this->load(fragmentShader);
    this->vertex_shader = vs.c_str();
    this->fragment_shader = fs.c_str();
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

    //this->vertex_shader = output.c_str();
    theFile.close();
    return output;
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

    model_matrix_ID = glGetUniformLocation(shaderProgram, "modelMatrix");
    projection_matrix_ID = glGetUniformLocation(shaderProgram, "projectionMatrix");
    view_matrix_ID = glGetUniformLocation(shaderProgram, "viewMatrix");
    cameraPosition_ID = glGetUniformLocation(shaderProgram, "cameraPosition");
    lightPos = glGetUniformLocation(shaderProgram, "lightPos");
    cameraDirection = glGetUniformLocation(shaderProgram, "cameraDirection");

    if (model_matrix_ID == -1 || projection_matrix_ID == -1 || view_matrix_ID == -1){
        std::cout << "cannot get matrix uniformLocation" << std::endl;
        exit(-1);
    }
    error_check();
}

void Shader::draw(glm::mat4 t_matrix) {
    this->projection = camera->getPerspective();
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(model_matrix_ID, 1, GL_FALSE, &t_matrix[0][0]);
    glUniformMatrix4fv(projection_matrix_ID, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(view_matrix_ID, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
    glUniformMatrix4fv(cameraDirection, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
    glUniform3fv(cameraPosition_ID, 1, glm::value_ptr(camera->getPosition()));
    glUniform3fv(lightPos, 1, glm::value_ptr(camera->getPosition()));
}

void Shader::error_check() {
    GLint status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
        GLint infoLogLength;
        glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
        std::cout << "linker failsure: " << strInfoLog;
        delete[] strInfoLog;
    }
}


void Shader::update(Subject& subject) {

}

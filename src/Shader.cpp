#include "../include/Shader.h"
#include "vector"
#include <iostream>
#include <fstream>
Shader::Shader(const std::string &vertexShader, Camera *&camera) {
    this->camera = camera;
    this->load(vertexShader);
    this->compile();
    this->vertex_shader = vertexShader.c_str();
}

int Shader::load(const std::string &vertexShader){
    std::string filepath = "../shaders/" + vertexShader;
    std::string temp;

    std::ifstream theFile(filepath);

    if(!theFile){
        std::cout << "could not find shader " << filepath << "\n";
        exit(-1);
    }

    while (getline (theFile, temp))
        output += temp + "\n";

    this->vertex_shader = output.c_str();

    theFile.close();
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

    if (model_matrix_ID == -1 || projection_matrix_ID == -1 || view_matrix_ID == -1){
        std::cout << "cannot get matrix uniformLocation" << std::endl;
        exit(-1);
    }
    error_check();
}

void Shader::draw(glm::mat4 t_matrix) {
    this->projection = camera->perspective();
    glUseProgram(shaderProgram);

    glUniformMatrix4fv(model_matrix_ID, 1, GL_FALSE, &t_matrix[0][0]);
    glUniformMatrix4fv(projection_matrix_ID, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(view_matrix_ID, 1, GL_FALSE, glm::value_ptr(camera->getCamera()));
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

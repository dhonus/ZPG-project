#include "../include/Shader.h"
#include "vector"
#include <iostream>

Shader::Shader() {
    this->compile();
}

void Shader::compile() {

    //create and compile shaders
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

    MatId = glGetUniformLocation(shaderProgram, "modelMatrix");
    if (MatId == -1){
        std::cout << "cannot get modelMatrix" << std::endl;
        exit(-1);
    }
}

void Shader::draw(glm::mat4 t_matrix) {
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(MatId, 1, GL_FALSE, &t_matrix[0][0]);
}

Shader::~Shader() {}

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

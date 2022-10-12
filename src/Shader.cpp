#include "../include/Shader.h"
#include "vector"
#include <iostream>
#include <fstream>
Shader::Shader(const std::string &vertexShader, std::shared_ptr<Camera> camera) {
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
    error_check();
}

void Shader::draw(glm::mat4 t_matrix) {
    //glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glUseProgram(shaderProgram);
    glUniformMatrix4fv(MatId, 1, GL_FALSE, &t_matrix[0][0]);

    glm::mat4 view = glm::mat4(1.0f);
    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    /*glm::vec3 eye {0.0f, -2.5f, -1.0f};
    view = glm::lookAt(eye,
                       eye + glm::vec3{0.f, 3.f, 1.f},
                       glm::vec3 {0.f, 1.f, 0.f});*/
    glm::mat4 projection;
    view = camera->getCamera();

    projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);

    int projectLoc = glGetUniformLocation(shaderProgram, "projectionMatrix");
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, glm::value_ptr(projection));

    int modelLoc = glGetUniformLocation(shaderProgram, "viewMatrix");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(view));
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

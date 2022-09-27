//
// Created by daniel on 26.9.22.
//

//Include GLFW
//Include GLEW
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>

//Include GLM
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

//Include the standard C++ headers
#include <stdlib.h>
#include <stdio.h>

#include "Window.h"
#include "Renderer.h"
#include "ShaderObject.h"
#include "App.h"

static void error_callback(int error, const char* description){ fputs(description, stderr); }

App::App() {
    window = new Window();
    glfwSetErrorCallback(error_callback);

    // start GLEW extension handler
    glewExperimental = GL_TRUE;
    glewInit();

    shaderObject = new ShaderObject();
}

int App::init() {

    //inicializace konkretni verze
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE,
    GLFW_OPENGL_CORE_PROFILE);

    GLint status;
    glGetProgramiv(shaderObject->shaderProgram, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        GLint infoLogLength;
        glGetProgramiv(shaderObject->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar *strInfoLog = new GLchar[infoLogLength + 1];
        glGetProgramInfoLog(shaderObject->shaderProgram, infoLogLength, NULL, strInfoLog);
        fprintf(stderr, "Linker failure: %s\n", strInfoLog);
        delete[] strInfoLog;
    }

    renderer = new Renderer(window, shaderObject->shaderProgram, shaderObject->VAO);

    glUseProgram(shaderObject->shaderProgram);
    glBindVertexArray(shaderObject->VAO);
    renderer->render();

    exit(EXIT_SUCCESS);
    return 0;
}

int App::close() {
    delete renderer;
    delete window;
    return 0;
}

//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_SHADER_H
#define OGL_TST_02_SHADER_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Vbo.h"
#include "Vao.h"
#include "Object.h"
#include "string"
#include "Camera.h"

class Object;
class Camera;

class Shader {
public:
    Shader(const std::string &vertexShader, std::shared_ptr<Camera> camera);
    ~Shader();
    void compile();
    void draw(glm::mat4 t_matrix);
    void error_check();

private:
    GLint MatId, ViewId;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    int load(const std::string &vertexShader);
    std::string output;
    std::shared_ptr<Camera> camera;

    // observer

    const char* vertex_shader;
    const char* fragment_shader =
          "#version 330\n"
          "out vec4 frag_colour;"
          "in vec4 colors;"
          "void main () {"
          "     frag_colour = colors;"
          "}";
};

#endif //OGL_TST_02_SHADER_H

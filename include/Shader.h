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
#include "Observer.h"

class Object;
class Camera;
class Observer;

class Shader : public Observer{
public:
    Shader(const std::string &vertexShader, Camera* camera);
    ~Shader() = default;
    void compile();
    void draw(glm::mat4 t_matrix);
    void error_check();
    void update(Subject& subject);
private:
    GLint model_matrix_ID, ViewId;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    int load(const std::string &vertexShader);
    std::string output;
    Camera* camera;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
    int projection_matrix_ID;
    int view_matrix_ID;

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

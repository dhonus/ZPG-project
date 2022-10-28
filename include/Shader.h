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
    Shader(const std::string &vertexShader, const std::string &fragmentShader, Camera *&camera);
    ~Shader() = default;
    void compile();
    void draw(glm::mat4 t_matrix);
    void error_check();
    void update(Subject& subject);
private:
    GLint model_matrix_ID,
        projection_matrix_ID,
        view_matrix_ID, cameraPosition_ID,
        lightPos, cameraDirection, fogToggle;
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    std::string load(const std::string &t_shader);
    std::string output;
    Camera* camera;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
    glm::mat4 camMatrix = glm::mat4(0.0f);

    const char* vertex_shader;
    const char* fragment_shader;

    float fog = 0.0f;

};

#endif //OGL_TST_02_SHADER_H

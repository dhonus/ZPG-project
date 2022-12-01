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
#include "Light.h"
#include <map>

class Object;
class Camera;
class Observer;
class Light;

class Shader : public Observer{
public:
    Shader(const std::string &vertexShader,
           const std::string &fragmentShader,
           Camera *&camera,
           const std::vector<std::shared_ptr<Light>> &lights, bool skybox);
    ~Shader() = default;
    void compile();
    void draw(glm::mat4 t_matrix, glm::vec3 t_objectColor);
    void error_check() const;
    void update(Subject& subject);
private:
    std::map<std::string, GLint> uniforms;

    GLint uniformMapper(const std::string &uniformName);
    GLuint shaderProgram;
    GLuint vertexShader;
    GLuint fragmentShader;
    std::string load(const std::string &t_shader);
    std::string output;
    Camera* camera;
    std::vector<std::shared_ptr<Light>> lights;
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 300.0f);
    glm::mat4 camMatrix = glm::mat4(0.0f);

    const char* vertex_shader;
    const char* fragment_shader;

    bool skybox;

    float fog = 1.0f;

    std::string fileName;

};

#endif //OGL_TST_02_SHADER_H

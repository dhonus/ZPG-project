//
// Created by daniel on 10/3/22.
//

#ifndef OGL_TST_02_OBJECT_H
#define OGL_TST_02_OBJECT_H

#include "Shader.h"
#include "Model.h"
#include "Trans.h"
#include <memory>
#include "string"
#include "Observer.h"

class Shader;
class Camera;

class Object {
public:
    Object(std::vector<float> b, const std::string& vertex_shader, Camera* camera);
    int draw();
    std::shared_ptr<Trans> trans;
private:
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    glm::mat4 matrix = glm::mat4(1.0f);
    std::string vertexShader{};
};

#endif //OGL_TST_02_OBJECT_H

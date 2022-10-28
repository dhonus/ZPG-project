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
#include "Scene.h"


class Shader;
class Camera;
class Scene;

class Object {
public:
    Object(const std::vector<float> &vertices, GLenum mode,
           int vertexCount, int posSize, int colSize, int colOffset, int genSize);
    Object(std::shared_ptr<Model> mod);
    int draw();
    Composite* add(std::shared_ptr<Composite> g);
    void remove(std::shared_ptr<Composite> g);
    Object* linkShader(std::shared_ptr<Shader> shader);
private:
    std::unique_ptr<Trans> trans;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    glm::mat4 matrix = glm::mat4(1.0f);
    std::string vertexShader{};
    std::string fragmentShader{};
};

#endif //OGL_TST_02_OBJECT_H

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
#include "Texture.h"

class Shader;
class Texture;
class Camera;
class Scene;

class Object {
public:
    Object(const std::vector<float> &vertices, GLenum mode,
           int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize, glm::vec3 t_color);
    Object(std::shared_ptr<Model> mod, glm::vec3 t_color);
    Object(const std::string& file_name, glm::vec3 t_color);
    int draw();
    Composite* add(std::shared_ptr<Composite> g);
    void remove(std::shared_ptr<Composite> g);
    Object* linkShader(std::shared_ptr<Shader> shader);
    Object* linkTexture(std::shared_ptr<Texture> texture);
    void setID(int t_id);
    int getID();
private:
    std::unique_ptr<Trans> trans;
    std::shared_ptr<Model> model;
    std::shared_ptr<Shader> shader;
    std::shared_ptr<Texture> texture;
    std::shared_ptr<Texture> normalMappingTexture;
    glm::mat4 matrix = glm::mat4(1.0f);
    std::string vertexShader{};
    std::string fragmentShader{};
    glm::vec3 color;
    int id = 0;
};

#endif //OGL_TST_02_OBJECT_H

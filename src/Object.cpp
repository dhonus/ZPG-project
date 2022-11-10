//
// Created by daniel on 10/3/22.
//

#include <iostream>
#include "../include/Object.h"

int Object::draw() {
    this->shader->draw(trans->getMatrix(), color);
    this->model->draw();
    return 0;
}

Object::Object(const std::vector<float> &vertices, GLenum mode,
               int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize, glm::vec3 t_color) {
    this->color = t_color;
    this->model = std::make_shared<Model>(vertices, mode, vertexCount, positionSize, normalsSize, normalsOffset, overallSize);
    this->trans = std::make_unique<Trans>();
}

Object::Object(std::shared_ptr<Model> mod, glm::vec3 t_color) {
    this->color = t_color;
    this->model = mod;
    this->trans = std::make_unique<Trans>();
}

Composite* Object::add(std::shared_ptr<Composite> obj){
    return this->trans->add(std::move(obj));
}

void Object::remove(std::shared_ptr<Composite> obj){
    this->trans->remove(std::move(obj));
}

Object* Object::linkShader(std::shared_ptr<Shader> shader) {
    this->shader = shader;
    return this;
}

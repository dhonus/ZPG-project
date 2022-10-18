//
// Created by daniel on 10/3/22.
//

#include <iostream>
#include "../include/Object.h"

int Object::draw() {
    this->shader->draw(trans->getMatrix());
    this->model->draw();
    return 0;
}

Object::Object(const std::vector<float> &vertices, const std::string &vertex_shader,
               const std::string &fragment_shader, Camera *&camera, GLenum mode,
               int vertexCount, int posSize, int colSize, int colOffset, int genSize) {
    this->vertexShader = vertex_shader;
    this->fragmentShader = fragment_shader;
    this->shader = std::make_shared<Shader>(this->vertexShader, this->fragmentShader, camera);
    this->model = std::make_shared<Model>(vertices, mode, vertexCount, posSize, colSize, colOffset, genSize);
    this->trans = std::make_unique<Trans>();
}

Composite* Object::add(std::shared_ptr<Composite> obj){
    return this->trans->add(std::move(obj));
}

void Object::remove(std::shared_ptr<Composite> obj){
    this->trans->remove(std::move(obj));
}

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

Object::Object(const std::vector<float> &vertices, GLenum mode,
               int vertexCount, int posSize, int colSize, int colOffset, int genSize) {
    this->model = std::make_shared<Model>(vertices, mode, vertexCount, posSize, colSize, colOffset, genSize);
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

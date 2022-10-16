//
// Created by daniel on 10/3/22.
//

#include <iostream>
#include "../include/Object.h"

int Object::draw() {
    shader->draw(trans->getMatrix());
    this->model->draw();
    return 0;
}

Object::Object(std::vector<float> b, const std::string &vertex_shader, Camera *&camera, GLenum mode, int vertexCount,
               int posSize, int colSize, int colOffset, int genSize) {
    this->vertexShader = vertex_shader;
    this->shader = std::make_shared<Shader>(this->vertexShader, camera);
    this->model = std::make_shared<Model>(b, mode, vertexCount, posSize, colSize, colOffset, genSize);
    this->trans = std::make_shared<Trans>();
}

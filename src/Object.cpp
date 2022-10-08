//
// Created by daniel on 10/3/22.
//

#include <iostream>
#include "../include/Object.h"

Object::Object(std::vector<float> b) {
    this->shader = std::make_shared<Shader>();
    this->model = std::make_shared<Model>(b);
    this->trans = std::make_shared<Trans>();
}

int Object::draw() {
    shader->draw(trans->getMatrix());
    this->model->draw();
    return 0;
}

//
// Created by daniel on 10/3/22.
//

#include <iostream>
#include "../include/Object.h"

int Object::draw() {
    this->shader->draw(trans->getMatrix(), color);

    if (texture != nullptr) {
        glActiveTexture(GL_TEXTURE0);
        texture->bind();
    }

    if (normalMappingTexture != nullptr) {
        glActiveTexture(GL_TEXTURE1);
        normalMappingTexture->bind();
    }

    this->model->draw();
    return 0;
}

Object::Object(const std::vector<float> &vertices, GLenum mode,
               int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize,
               glm::vec3 t_color) {
    this->color = t_color;
    this->model = std::make_shared<Model>(vertices, mode, vertexCount, positionSize, normalsSize, normalsOffset,
                                          overallSize);
    this->trans = std::make_unique<Trans>();
    std::cout << "\t[->] Created object from vertices" << std::endl;
}

Object::Object(std::shared_ptr<Model> mod, glm::vec3 t_color) {
    this->color = t_color;
    this->model = mod;
    this->trans = std::make_unique<Trans>();
}

Composite *Object::add(std::shared_ptr<Composite> obj) {
    return this->trans->add(std::move(obj));
}

void Object::remove(std::shared_ptr<Composite> obj) {
    this->trans->remove(std::move(obj));
}

Object *Object::linkShader(std::shared_ptr<Shader> shader) {
    this->shader = shader;

    return this;
}

Object *Object::linkTexture(std::shared_ptr<Texture> texture) {
    if (this->texture == nullptr) {
        this->texture = texture;
        return this;
    }
    if (this->normalMappingTexture == nullptr) {
        this->normalMappingTexture = texture;
        return this;
    }

    std::cout << "[!!] No texture slot available\n" << std::flush;
    return this;
}

Object::Object(const std::string& file_name, glm::vec3 t_color) {
    this->color = t_color;
    this->model = std::make_shared<Model>(file_name);
    this->trans = std::make_unique<Trans>();
    std::cout << "\t[->] Created object from file: " << file_name << std::endl;
}

void Object::setID(int t_id) {
    this->id = t_id;
}

int Object::getID() {
    return this->id;
}

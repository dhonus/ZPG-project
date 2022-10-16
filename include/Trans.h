//
// Created by daniel on 10/8/22.
//

#ifndef OGL_TST_02_TRANS_H
#define OGL_TST_02_TRANS_H

#include <glm/ext/matrix_float4x4.hpp>
#include <algorithm>
#include <iostream>
#include <list>
#include <GLFW/glfw3.h>
#include "memory"

class Composite {
public:
    virtual glm::mat4 transform() const = 0;
    virtual void remove(Composite &g) {}
    virtual Composite* add(std::shared_ptr<Composite> g) { return nullptr; }
    virtual void getChild(int) {}
    virtual ~Composite() = default;
protected:
    glm::mat4 current{1.0f};
};

class TransRotate : public Composite {
public:
    TransRotate(float speed, glm::vec3 position, glm::vec3 axis);
    TransRotate(bool stationary, float speed, glm::vec3 position, glm::vec3 axis);
    glm::mat4 transform() const override;
private:
    glm::vec3 position;
    glm::vec3 axis;
    float speed;
    bool stationary = false;
};

class TransScale : public Composite {
public:
    explicit TransScale(float factor);
    glm::mat4 transform() const override;
private:
    float factor;
};

class TransMove : public Composite {
public:
    TransMove(glm::vec3 moveDirection);
    glm::mat4 transform() const override;
private:
    glm::vec3 moveDirection;
};


class Trans : public Composite {
public:
    glm::mat4 getMatrix();
    Trans();
    ~Trans() override;

    glm::mat4 transform() const override;
    Composite* add(std::shared_ptr<Composite> transformation);

private:
    std::list<std::shared_ptr<Composite>> transformations;
};

#endif //OGL_TST_02_TRANS_H

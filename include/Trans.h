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
    virtual glm::mat4 transform() = 0;
    virtual void remove(std::shared_ptr<Composite> g) {}
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
    glm::mat4 transform() override;
private:
    glm::vec3 position;
    glm::vec3 axis;
    float speed;
    bool stationary = false;
};

class TransScale : public Composite {
public:
    explicit TransScale(float factor);
    glm::mat4 transform()  override;
private:
    float factor;
};

class TransMove : public Composite {
public:
    TransMove(glm::vec3 moveDirection);
    glm::mat4 transform()  override;
private:
    glm::vec3 moveDirection;
    glm::mat4 mod {1.0f};
};

class TransParMove : public Composite {
public:
    TransParMove(glm::mat4 A, glm::mat4 B, float speed, bool curve);
    glm::mat4 transform()  override;
private:
    glm::mat4 A;
    glm::mat4 B;
    float t = 0.5f;
    float delta = 0.01f;
    float speed;
    bool curve;
};


class Trans : public Composite {
public:
    glm::mat4 getMatrix();
    Trans();
    ~Trans() override;

    glm::mat4 transform()  override;
    Composite* add(std::shared_ptr<Composite> transformation);
    void remove(std::shared_ptr<Composite> transformation);

private:
    std::list<std::shared_ptr<Composite>> transformations;
};

#endif //OGL_TST_02_TRANS_H

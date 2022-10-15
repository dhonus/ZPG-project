//
// Created by daniel on 10/8/22.
//

#ifndef OGL_TST_02_TRANS_H
#define OGL_TST_02_TRANS_H

#include <glm/ext/matrix_float4x4.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include <list>
#include <string>

class Composite {
public:
    virtual glm::mat4 transform() const = 0;
    virtual void remove(Composite *g) {}
    virtual void add(Composite *g) {}
    virtual void getChild(int) {}
    virtual ~Composite() {}
protected:
    glm::mat4 current{1.0f};
};

class TransRotate : public Composite {
public:
    TransRotate(float deg, float quantifier, glm::vec3 axis){
        this->deg = deg;
        this->quantifier = quantifier;
        this->axis = axis;
    }
    glm::mat4 transform() const {
        glm::mat4 normal (1.0f);
        normal = glm::rotate(normal, glm::radians(deg), axis);
        normal = glm::translate(normal, glm::vec3(0.0f));
        return normal;
    }
private:
    float deg;
    float quantifier;
    glm::vec3 axis;
};

class TransScale : public Composite {
public:
    glm::mat4 transform() const {
        return glm :: scale (glm::mat4{1.0f} , glm :: vec3 (0.999f));
    }
};

class TransMove : public Composite {
public:
    TransMove(glm::vec3 moveDirection){
        this->moveDirection = moveDirection;
    }
    glm::mat4 transform() const {
        glm::mat4 mod {1.0f};
        glm::rotate(mod, glm::radians(1.0f), moveDirection);
        mod = glm::translate(mod, 0.5f * moveDirection);
        return mod;
    }
private:
    glm::vec3 moveDirection;
};


class Trans : public Composite {
public:
    glm::mat4 getMatrix();
    Trans();
    ~Trans(){
        for (auto& trans : transformations){
            delete trans;
        }
    }

    glm::mat4 transform() const {
        // for each element in transformations, call the transform member function
        glm::mat4 mod {1.0f};
        for (auto& trans : transformations){
            mod *= trans->transform();
        }
        return mod;
    }
    void add(Composite *transformation) {
        transformations.push_back(transformation);
    }

private:
    std::vector<Composite*> transformations;
};

#endif //OGL_TST_02_TRANS_H

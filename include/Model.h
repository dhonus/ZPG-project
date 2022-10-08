//
// Created by daniel on 10/8/22.
//

#ifndef OGL_TST_02_MODEL_H
#define OGL_TST_02_MODEL_H

#include "Vbo.h"
#include "Vao.h"
#include <memory>

class Model {
public:
    Model(std::vector<float> b);
    int draw();
private:
    std::shared_ptr<Vbo> VBO;
    std::shared_ptr<Vao> VAO;
};

#endif //OGL_TST_02_MODEL_H

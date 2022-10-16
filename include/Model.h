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
    Model(const std::vector<float> &vertices, GLenum mode, int vertexCount, int posSize, int colSize, int colOffset, int genSize);
    int draw();
private:
    std::shared_ptr<Vbo> VBO;
    std::shared_ptr<Vao> VAO;
    GLenum mode;
    int vertexCount;
};

#endif //OGL_TST_02_MODEL_H

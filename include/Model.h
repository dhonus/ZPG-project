//
// Created by daniel on 10/8/22.
//

#ifndef OGL_TST_02_MODEL_H
#define OGL_TST_02_MODEL_H

#include "Vbo.h"
#include "Vao.h"
#include <memory>
#include "Mesh.h"

class Model {
public:
    Model(const std::vector<float> &vertices, GLenum mode, int vertexCount, int positionSize, int normalsSize, int normalsOffset, int overallSize);
    Model(const std::string fileName);
    int draw();
private:
    std::shared_ptr<Mesh> mesh;
};

#endif //OGL_TST_02_MODEL_H

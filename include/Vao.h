#ifndef OGL_TST_02_VAO_H
#define OGL_TST_02_VAO_H

#include <GL/glew.h>
#include "Vbo.h"
#include <memory>
class Vbo;

class Vao {
public:
    Vao(std::shared_ptr<Vbo> vbo);
    void bind_vertex_array();

private:
    GLuint VAO;
};

#endif //OGL_TST_02_VAO_H

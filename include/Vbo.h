//
// Created by daniel on 27.9.22.
//

#ifndef OGL_TST_02_VBO_H
#define OGL_TST_02_VBO_H

#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>
#include <glm/vec4.hpp>

class Vbo {
private:
    GLuint VBO;
    std::vector<float> points;
    int posSize;
    int colSize;
    int colOffset;
    int genSize;
public:
    Vbo(std::vector<float> &t_points, int posSize, int colSize, int colOffset, int genSize);
    Vbo();
    void bind_buffer();
};


#endif //OGL_TST_02_VBO_H

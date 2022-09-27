//
// Created by daniel on 27.9.22.
//

#ifndef OGL_TST_02_VBO_H
#define OGL_TST_02_VBO_H

#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h>
#include <vector>

class Vbo {
private:
    GLuint VBO;
public:
    Vbo(std::vector<float> t_points);
    void bind_buffer();
};



#endif //OGL_TST_02_VBO_H

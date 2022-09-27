//
// Created by daniel on 26.9.22.
//

#ifndef OGL_TST_02_SHADEROBJECT_H
#define OGL_TST_02_SHADEROBJECT_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class ShaderObject {
public:
    ShaderObject();
    GLuint shaderProgram;
    GLuint VAO;
private:
    const char* vertex_shader =
            "#version 330\n"
            "layout(location=0) in vec3 vp;"
            "out vec3 colors;"
            "void main () {"
            "     gl_Position = vec4 (vp, 1.0);"
            "     colors = vp;"
            "}";
    const char* fragment_shader =
            "#version 330\n"
            "out vec4 frag_colour;"
            "in vec3 colors;"
            "void main () {"
            "     frag_colour = vec4 (colors, 1.0);"
            "}";
};


#endif //OGL_TST_02_SHADEROBJECT_H

#version 330

layout(location=0) in vec4 vp;
layout(location=1) in vec4 color;
out vec4 colors;
uniform mat4 modelMatrix;
void main () {
     gl_Position = modelMatrix*vp;
     colors = modelMatrix*color;
}
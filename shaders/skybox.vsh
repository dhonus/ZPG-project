#version 330
layout (location = 0) in vec4 aPos;
out vec3 coordinates;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    // only keep rotation
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix*view*modelMatrix*aPos;
    coordinates = vec3(aPos);
}
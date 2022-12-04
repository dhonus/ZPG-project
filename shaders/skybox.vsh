#version 330
layout (location = 0) in vec4 vertexPosition;
out vec3 coordinates;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    mat4 viewAdjusted = mat4(mat3(viewMatrix));
    gl_Position = projectionMatrix*viewAdjusted*vertexPosition;
    coordinates = vertexPosition.xyz / vertexPosition.w;
}
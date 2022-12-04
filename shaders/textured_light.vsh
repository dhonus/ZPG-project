#version 330

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec4 modelNormals;
layout (location = 2) in vec2 textureCoordinates;
out vec2 textureCoordinatesOut;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vertexPosition;
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
    Normal = normalMatrix * modelNormals.xyz;
    FragPos = vec3(modelMatrix*vertexPosition);
    textureCoordinatesOut.x = textureCoordinates.x;
    textureCoordinatesOut.y = -textureCoordinates.y;
}
#version 330

layout(location=0) in vec4 vertexPosition;
layout(location=1) in vec4 modelNormals;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform mat4 normalMatrix;
void main () {
    mat4 model = mat4(1.0f);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vertexPosition;
    Normal = vec3(modelNormals);
    FragPos = vec3(modelMatrix*vertexPosition);
}
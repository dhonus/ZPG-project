#version 330

layout(location=0) in vec4 aPos;
layout(location=1) in vec4 aNormal;
out vec3 Normal;
out vec3 worldPosition;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform mat4 normalMatrix;

void main () {
    Normal = normalize(transpose(inverse(mat3(modelMatrix))) * vec3(aNormal));
    FragPos = vec3(modelMatrix * aPos);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*aPos;
    worldPosition = vec3(modelMatrix * aPos);
}
#version 330

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoord;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*aPos;
    Normal = vec3(aNormal);
    FragPos = vec3(modelMatrix*aPos);
    TexCoord.x = aTexCoord.x;
    TexCoord.y = -aTexCoord.y;
}
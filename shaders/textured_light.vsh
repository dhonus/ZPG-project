#version 330

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoord;
out vec3 ourColor;
out vec3 coordinates;
out vec2 TexCoord;
out vec3 Normal;
out vec4 colors;
in vec3 worldPosition;
in vec3 worldNormal;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform mat4 normalMatrix;

void main () {
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*aPos;
    colors = aNormal;
    Normal = vec3(aNormal);
    FragPos = vec3(modelMatrix*aPos);
    ourColor = vec3(aNormal);
    TexCoord.x = aTexCoord.x;
    TexCoord.y = -aTexCoord.y;
}
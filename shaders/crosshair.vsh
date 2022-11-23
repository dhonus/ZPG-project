#version 330

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoord;
out vec3 coordinates;
in vec3 worldPosition;
in vec3 worldNormal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform mat4 normalMatrix;
out vec2 TexCoord;
void main () {
    // remove translation
    mat4 view = mat4(mat3(viewMatrix));
    gl_Position = aPos*modelMatrix;
    coordinates = vec3(aPos);
    TexCoord.x = aTexCoord.x;
    TexCoord.y = -aTexCoord.y;
}
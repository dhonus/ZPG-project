#version 330

layout(location=0) in vec4 aPos;
layout(location=1) in vec4 aNormal;
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
    //Normal = vec3(mat3(transpose(inverse(modelMatrix))) * nvec3(aNormal));
    FragPos = vec3(modelMatrix*aPos);

}
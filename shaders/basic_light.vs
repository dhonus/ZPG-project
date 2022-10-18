#version 330

layout(location=0) in vec4 vp;
layout(location=1) in vec4 normals;
out vec4 colors;
out vec4 camPos;
out vec4 worldPosition;
out vec3 worldNormal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
//uniform mat4 normalMatrix;
void main () {
     gl_Position = projectionMatrix*viewMatrix*modelMatrix*vp;
     mat4 normal = modelMatrix;
     worldNormal = vec3(normal * normals);
     worldPosition = modelMatrix * normals;
     camPos = gl_Position;
     //colors = color;
}
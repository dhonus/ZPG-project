#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
in vec3 worldPosition;
in vec3 LightingColor;

uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 lightPos;

void main () {
    frag_colour = vec4(LightingColor, 1.0f);
}
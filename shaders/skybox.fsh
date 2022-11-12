#version 330
out vec4 frag_colour;

uniform samplerCube ourTexture;
in vec3 coordinates;

void main () {
    frag_colour = texture(ourTexture, coordinates);
}
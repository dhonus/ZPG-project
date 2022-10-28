#version 330
out vec4 frag_colour;
in vec4 colors;
smooth in vec3 ex_UV;
smooth in vec3 ex_originalPosition;
in vec3 worldPosition;

void main () {
    frag_colour = vec4(0.1f, 0.1f, 0.1f, 1.0f);
    float lineWidth = 0.05;
    if (fract(worldPosition.x / 5.0f) < 0.01 && fract(worldPosition.x / 5.0f) > -0.01){
        frag_colour = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }
    if (fract(worldPosition.z / 5.0f) < 0.01 && fract(worldPosition.z / 5.0f) > -0.01){
        frag_colour = vec4(0.2f, 0.2f, 0.2f, 1.0f);
    }
    if (fract(worldPosition.x / 20.0f) < 0.005 && fract(worldPosition.x / 20.0f) > -0.005){
        frag_colour = vec4(0.7f, 0.7f, 0.7f, 1.0f);

    }
    if (fract(worldPosition.z / 20.0f) < 0.005 && fract(worldPosition.z / 20.0f) > -0.005){
        frag_colour = vec4(0.7f, 0.7f, 0.7f, 1.0f);
    }

    float distance = length(worldPosition);
    float attenuation = 100.0 / (50.0 + 0.09f * distance +
                               0.032f * (distance * distance));
    frag_colour *= attenuation;

}
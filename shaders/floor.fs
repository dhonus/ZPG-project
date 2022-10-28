#version 330
out vec4 frag_colour;
in vec4 colors;
smooth in vec3 ex_UV;
smooth in vec3 ex_originalPosition;
in vec3 worldPosition;
uniform vec3 cameraPosition;
uniform float foggy;

vec4 fog(vec4 f){
// Fog parameters, could make them uniforms and pass them into the fragment shader
float fog_maxdist = 90;
float fog_mindist = 0.1;
vec4  fog_colour = vec4(0.4, 0.4, 0.4, 1.0);

// Calculate fog
float dist = length(worldPosition - cameraPosition);
float fog_factor = (fog_maxdist - dist) /
                   (fog_maxdist - fog_mindist);
fog_factor = clamp(fog_factor, 0.0, 1.0);

return mix(fog_colour, f, fog_factor);
}

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
    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
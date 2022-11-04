#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
in vec3 worldPosition;
in vec3 LightingColor;

uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 lightPos;
uniform float foggy;


vec4 fog(vec4 f){
    // Fog parameters, could make them uniforms and pass them into the fragment shader
    float fog_maxdist = 90;
    float fog_mindist = 0.1;
    vec4  fog_colour = vec4(0.4, 0.4, 0.4, 1.0);

    // Calculate fog
    float dist = length(FragPos - cameraPosition);
    float fog_factor = (fog_maxdist - dist) /
                       (fog_maxdist - fog_mindist);
    fog_factor = clamp(fog_factor, 0.0, 1.0);

    return mix(fog_colour, f, fog_factor);
}

void main () {
    frag_colour = vec4(LightingColor, 1.0f);
    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
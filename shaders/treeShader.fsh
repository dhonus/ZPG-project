#version 330
out vec4 frag_colour;
in vec4 colors;
in vec3 Normal;
in vec3 FragPos;
in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 lightPos;
uniform float foggy;

vec4 fog(vec4 f){
    float fog_maxdist = 180;
    float fog_mindist = 100;
    vec4  fog_colour = vec4(0.0, 0.0, 0.0, 0.0);

    // Calculate fog
    float dist = length(FragPos - cameraPosition);
    float fog_factor = (fog_maxdist - dist) /
    (fog_maxdist - fog_mindist);
    fog_factor = clamp(fog_factor, 0.0, 1.0);

    return mix(fog_colour, f, fog_factor);
}


void main () {
    float ambientStrength = 0.1f;
    vec3 color = u_objectColor * u_lightColor;

    vec3 ambientLight = (ambientStrength * color);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
    vec4 diffuse = dot_product * vec4(color, 1.0f);

    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(vec3(cameraDirection));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * color;

    frag_colour = vec4(ambientLight, 1.0f) + vec4(specular, 1.0f) + diffuse;
    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
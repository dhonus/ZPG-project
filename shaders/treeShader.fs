#version 330
out vec4 frag_colour;
in vec4 colors;
in vec3 Normal;
in vec3 FragPos;
in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
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
    float ambientStrength = 0.1f;
    vec3 lightColor = vec3(0.2f, 0.4f, 0.2f);
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = (ambientStrength * lightColor) * objectColor*vec3(colors)/2;

    vec3 lightPos = vec3(20.0f, -5.0f, 20.0f);

    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor;

    float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
    vec4 diffuse = dot_product * vec4(lightColor, 1.0f);



    // specular
    float specularStrength = 0.5;
    //(vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 viewDir = normalize(vec3(cameraDirection));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;


    //frag_colour = vec4(ambientLight, 1.0f) + vec4(diffuse, 1.0f);
    frag_colour = vec4(ambientLight, 1.0f) + vec4(specular, 1.0f) + diffuse;
    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
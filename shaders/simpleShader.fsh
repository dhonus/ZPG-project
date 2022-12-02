#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
uniform vec3 cameraPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform vec3 lightPos;
uniform float foggy;

vec4 fog(vec4 fragmentColor){
    float fogMinDistance = 100;
    float fogMaxDistance = 180;
    vec4 fogColor = vec4(0.0, 0.0, 0.0, 0.0);

    // Calculate fog
    float fogDistance = length(FragPos - cameraPosition);
    float fogFactor = (fogMaxDistance - fogDistance) / (fogMaxDistance - fogMinDistance);
    fogFactor = clamp(fogFactor, 0.0, 1.0);

    return mix(fogColor, fragmentColor, fogFactor);
}

void main () {
    float ambientStrength = 0.1f;
    vec3 computedColor = objectColor * lightColor;

    /* AMBIENT */
    vec3 ambient = (ambientStrength * computedColor);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    /* DIFFUSE */
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * computedColor;

    /* SPECULAR */
    float specularStrength = 0.3f;
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);
    vec3 specular = specularStrength * spec * computedColor;

    frag_colour = vec4(ambient + specular + diffuse, 1.0f);

    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
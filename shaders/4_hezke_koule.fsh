#version 330

in vec3 Normal;
in vec3 FragPos;
out vec4 frag_colour;

uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 lightPos;

void main () {
    // ambient
    float ambientStrength = 0.2f;

    vec3 lightColor =  vec3(0.4f, 0.4f, 0.4f);
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);

    vec3 computedColor = objectColor * lightColor;

    /* AMBIENT */
    vec3 ambient = (ambientStrength * computedColor);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);

    /* DIFFUSE */
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * computedColor;

    /* SPECULAR */
    float specularStrength = 1.0f;
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0f);
    vec3 specular = specularStrength * spec * computedColor;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }

    frag_colour = vec4(ambient + specular + diffuse, 1.0f);
}
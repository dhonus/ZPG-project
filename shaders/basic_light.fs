#version 330
out vec4 frag_colour;
in vec4 normals;
in vec4 camPos;
in vec4 worldPosition;
in vec3 worldNormal;
void main () {
    // specular
    float specularStrength = 1;
    vec3 norm = normalize(worldNormal);
    vec3 lightPosition = vec3(5.0, -10.0, 7.0);
    vec3 lightDir = normalize(lightPosition - vec3(worldPosition));

    // diffuse
    float diff = max(dot(worldNormal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);
    vec3 viewDir = normalize(vec3(camPos - worldPosition));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);

    // ambient
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    frag_colour = ambient + vec4(specular + diffuse, 1.0f);
}
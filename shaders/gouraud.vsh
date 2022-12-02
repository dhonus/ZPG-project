#version 330

layout(location=0) in vec4 vertexPosition;
layout(location=1) in vec4 modelNormals;

out vec3 Normal;
out vec3 worldPosition;
out vec3 FragPos;
out vec3 LightingColor;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main () {
    Normal = normalize(transpose(inverse(mat3(modelMatrix))) * vec3(modelNormals));
    FragPos = vec3(modelMatrix * vertexPosition);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix* vertexPosition;
    worldPosition = vec3(modelMatrix * vertexPosition);

    vec3 computedColor = objectColor * lightColor;

    float ambientStrength = 0.5f;

    /* AMBIENT */
    vec3 ambient = (ambientStrength * computedColor);

    /* DIFFUSE */
    vec3 lightPosition = vec3(15.0f, 5.0f, 10.0f);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * computedColor;

    /* SPECULAR */
    float specularStrength = 2.0f;
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 4.0);
    vec3 specular = specularStrength * spec * computedColor;

    LightingColor = ambient + diffuse + specular;
}
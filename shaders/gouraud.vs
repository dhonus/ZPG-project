#version 330

layout(location=0) in vec4 aPos;
layout(location=1) in vec4 aNormal;
out vec3 Normal;
out vec3 worldPosition;
out vec3 FragPos;
out vec3 LightingColor;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;
uniform mat4 normalMatrix;

void main () {
    Normal = normalize(transpose(inverse(mat3(modelMatrix))) * vec3(aNormal));
    FragPos = vec3(modelMatrix * aPos);
    gl_Position = projectionMatrix*viewMatrix*modelMatrix*aPos;
    worldPosition = vec3(modelMatrix * aPos);

    // ambient
    vec3 ambientColor = vec3(0.4f, 0.4f, 0.4f);
    float ambientStrength = 0.4f;
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = (ambientStrength * ambientColor) * objectColor;

    // diffuse
    vec3 lightPosition = vec3(15.0f, 5.0f, 10.0f);
    vec3 lightColor = vec3(0.7f, 0.5f, 0.7f);
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - worldPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 4;
    vec3 viewDir = normalize(cameraPosition - worldPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;

    //frag_colour = vec4(specular, 1.0f);
    LightingColor = ambientLight + diffuse + specular;
}
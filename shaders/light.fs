#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
in vec3 worldNormal;
in vec3 worldPosition;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 lightPos;

void main () {
    // ambient
    vec3 ambientColor = vec3(0.4f, 0.4f, 0.4f);
    float ambientStrength = 0.20f;
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = (ambientStrength * ambientColor) * objectColor;

    // diffuse
    //vec3 lightPosition = vec3(0.0, 10.0, 0.0);
    vec3 lightColor = vec3(0.7f, 0.5f, 0.7f);
    float distance = length(lightPos - FragPos);
    float attenuation = 1.0 / (1.0 + 0.09f * distance +
            0.032f * (distance * distance));
    vec3 norm = normalize(vec3(Normal));
    vec3 lightDir = normalize(lightPos - vec3(FragPos));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    diffuse*= attenuation;

    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),128);
    vec3 specular = specularStrength * spec * lightColor;
    specular*=attenuation;


    //frag_colour = vec4(specular, 1.0f);
    frag_colour = vec4(ambientLight, 1.0f) + vec4(diffuse, 1.0f) + vec4(specular, 1.0f);

}
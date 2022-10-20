#version 330
out vec4 frag_colour;
in vec4 FragPos;
in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
void main () {
    // specular
    /*float specularStrength = 1;
    vec3 viewDir = normalize(vec3(camPos - FragPos));
    vec3 norm = normalize(vec3(worldNormal));
    vec3 lightPosition = vec3(5.0, -10.0, 7.0);
    vec3 lightDir = normalize(lightPosition - vec3(worldPosition));

    // diffuse
    float diff = max(dot(worldNormal, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0f, 1.0f, 1.0f);

    // ambient
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    //frag_colour = ambient + vec4(specular + diffuse, 1.0f);
    frag_colour = vec4(specular, 1.0f);*/

    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);

    // ambient
    vec4 ambient = vec4( 0.1, 0.1, 0.1, 1.0);

    // diffuse
    vec3 lightPosition = vec3(0.0, -5.0, 0.0);
    vec3 norm = normalize(vec3(worldNormal));
    vec3 lightDir = normalize(lightPosition - vec3(FragPos));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(vec3(vec4(cameraPosition, 1.0f) - FragPos));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;


    frag_colour = vec4(diffuse, 1.0f) + vec4(specular, 1.0f) + ambient;
}
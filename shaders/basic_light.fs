#version 330
out vec4 frag_colour;
in vec4 colors;
in vec3 Normal;
in vec3 FragPos;
in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;

uniform vec3 lightPos;
void main () {

    float ambientStrength = 0.1f;
    vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = (ambientStrength * lightColor) * objectColor*vec3(colors)/2;


    vec3 norm = normalize(Normal);
    //vec3 lightDir = normalize(lightPos - FragPos);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    //vec3 diffuse = diff * lightColor;

    float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
    vec4 diffuse = dot_product * vec4( 0.385, 0.647, 0.812, 1.0);



    // specular
    float specularStrength = 0.5;
    //(vec3 viewDir = normalize(cameraPosition - FragPos);
    vec3 viewDir = normalize(vec3(cameraDirection));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8);
    vec3 specular = specularStrength * spec * lightColor;


    //frag_colour = vec4(ambientLight, 1.0f) + vec4(diffuse, 1.0f);
    frag_colour = vec4(ambientLight, 1.0f) + vec4(specular, 1.0f) + diffuse;

}
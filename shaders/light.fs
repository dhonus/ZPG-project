#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
in vec3 worldNormal;
in vec3 worldPosition;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 lightPos;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform float foggy;


vec4 fog(vec4 f){
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

struct LightStruct {
    int type;
    vec3 position;
    vec3 direction;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define MAX_LIGHTS 2
uniform LightStruct pointLights[MAX_LIGHTS];

vec3 point_light(LightStruct light, vec3 norm, vec3 viewDir)
{
    // ambient
    vec3 ambientColor = vec3(0.4f, 0.4f, 0.4f);
    float ambientStrength = 0.20f;
    //vec3 objectColor = vec3(1.0f, 1.0f, 1.0f);
    vec3 ambientLight = (ambientStrength * ambientColor) * u_objectColor;

    // diffuse
    //vec3 lightPosition = vec3(0.0, 10.0, 0.0);
    vec3 lightColor = vec3(0.5f, 0.5f, 0.0f);
    float distance = length(cameraPosition - FragPos);
    float attenuation = 3.0 / (2.0 + 0.09f * distance +
                               0.01f * (distance * distance));
    vec3 lightDir = normalize(cameraPosition - vec3(FragPos));
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_lightColor;
    diffuse*= attenuation;

    // specular
    float specularStrength = 1;
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0),128);
    vec3 specular = specularStrength * spec * u_lightColor;
    specular*=attenuation;

    return (ambientLight+diffuse+specular);
}

void main () {

    LightStruct l;

    //frag_colour = vec4(specular, 1.0f);
    vec3 norm = normalize(vec3(Normal));
    vec3 viewDir = normalize(cameraPosition - FragPos);

    frag_colour = vec4(point_light(l, norm, viewDir), 1.0f);

    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }

}
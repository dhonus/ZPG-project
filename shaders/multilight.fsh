#version 330
out vec4 frag_colour;
in vec4 colors;
in vec3 Normal;
in vec3 FragPos;
in vec4 worldPosition;
in vec3 worldNormal;
uniform vec3 cameraPosition;
uniform mat4 cameraDirection;
uniform vec3 u_lightColor;
uniform vec3 u_objectColor;
uniform vec3 lightPos;
uniform float foggy;


struct lightStruct {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;

    float constant;
    float linear;
    float quadratic;
    float cutoff;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

//#define MAX_LIGHTS 16
const int MAX_LIGHTS = 16;
uniform lightStruct lights[MAX_LIGHTS];
uniform int how_many_lights;

vec3 point_light(lightStruct light) {
    float ambientStrength = 0.1f;
    vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;
    vec3 lightDir = normalize(light.position - FragPos);

    // ambient
    vec3 ambient = (ambientStrength * color);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
    vec3 diffuse = dot_product * color;

    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(vec3(cameraDirection));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0f);
    vec3 specular = specularStrength * spec * color;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }
    return (ambient + diffuse + specular);
}

vec3 directional_light(lightStruct light) {
    vec3 lightDir = normalize(-light.direction);
    vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = (ambientStrength * color);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
    vec3 diffuse = dot_product * color;

    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(cameraPosition - vec3(worldPosition));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = specularStrength * spec * color;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }
    return (ambient + diffuse + specular);
}

vec3 spot_light(lightStruct light) {
    vec3 lightDir = normalize(light.position - FragPos);
    vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = (ambientStrength * color);

    float theta = dot(lightDir, normalize(-light.direction));
    if(theta > cos(radians(light.cutoff))){

        float distance    = length(light.position - FragPos);
        float attenuation = 5.0 / (3.0 + 0.09 * distance + 0.032 * (distance * distance));
        float intensity = (1.0 - (1.0 - theta) / (1.0 - cos(radians(light.cutoff))));

        // diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        float dot_product = max(dot(lightDir, normalize(Normal)), 0.0);
        vec3 diffuse = dot_product * color * attenuation * intensity;

        // specular
        float specularStrength = 1;
        vec3 viewDir = normalize(cameraPosition - vec3(worldPosition));
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
        vec3 specular = specularStrength * spec * color * attenuation * intensity;

        if (dot(norm, lightDir) < 0.0){
            specular = vec3(0.0f, 0.0f, 0.0f);
        }
        return (ambient + diffuse + specular);
    }

    return ambient;
}

vec4 fog(vec4 f){
    float fog_maxdist = 180;
    float fog_mindist = 100;
    vec4  fog_colour = vec4(0.0, 0.0, 0.0, 0.0);

    // Calculate fog
    float dist = length(FragPos - cameraPosition);
    float fog_factor = (fog_maxdist - dist) /
    (fog_maxdist - fog_mindist);
    fog_factor = clamp(fog_factor, 0.0, 1.0);

    return mix(fog_colour, f, fog_factor);
}

void main () {
    lightStruct l;
    // vec3 three = four.xyz / four.w;

    frag_colour = vec4(0.0f);

    for(int i = 0; i < how_many_lights; i++){
        lights[i].type == 1 ? frag_colour = frag_colour + vec4(point_light(lights[i]), 1.0f) : frag_colour;
        lights[i].type == 2 ? frag_colour = frag_colour + vec4(directional_light(lights[i]), 1.0f) : frag_colour;
        lights[i].type == 3 ? frag_colour = frag_colour + vec4(spot_light(lights[i]), 1.0f) : frag_colour;
    }
    if (foggy == 1.0f){
        frag_colour = fog(frag_colour);
    }
}
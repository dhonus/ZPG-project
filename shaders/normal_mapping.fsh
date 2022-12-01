#version 330
out vec4 frag_colour;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoord;
in mat3 tbn;
uniform vec3 cameraPosition;
uniform vec3 u_objectColor;
uniform float foggy;
uniform sampler2D objectTexture;
uniform sampler2D normalTexture;

struct lightStruct {
    int type;
    vec3 position;
    vec3 direction;
    vec3 color;

    float cutoff;
};

//#define MAX_LIGHTS 16
const int MAX_LIGHTS = 16;
uniform lightStruct lights[MAX_LIGHTS];
uniform int how_many_lights;

vec3 point_light(lightStruct light, vec3 norm) {
    float ambientStrength = 0.1f;
    //vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;
    vec3 lightDir = normalize(light.position - FragPos);

    // ambient
    vec3 ambient = (ambientStrength * color);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color;

    // specular
    float specularStrength = 0.3f;
    vec3 viewDir = normalize(cameraPosition - vec3(FragPos));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    vec3 specular = specularStrength * spec * color;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }
    return (ambient + diffuse + specular);
}

vec3 directional_light(lightStruct light, vec3 norm) {
    vec3 lightDir = normalize(-light.direction);
    //vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = (ambientStrength * color);

    // diffuse
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * color;

    // specular
    float specularStrength = 0.3f;
    vec3 viewDir = normalize(cameraPosition - vec3(FragPos));
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    vec3 specular = specularStrength * spec * color;

    if (dot(norm, lightDir) < 0.0){
        specular = vec3(0.0f, 0.0f, 0.0f);
    }
    return (ambient + diffuse + specular);
}

vec3 spot_light(lightStruct light, vec3 norm) {
    vec3 lightDir = normalize(light.position - FragPos);
    //vec3 norm = normalize(Normal);
    vec3 color = u_objectColor * light.color;

    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = (ambientStrength * color);

    float theta = dot(lightDir, normalize(-light.direction));
    if(theta > cos(radians(light.cutoff))){

        float distance = length(light.position - FragPos);
        float attenuation = 5.0 / (3.0 + 0.09 * distance + 0.012 * (distance * distance));
        float intensity = (1.0 - (1.0 - theta) / (1.0 - cos(radians(light.cutoff))));

        // diffuse
        float diff = max(dot(norm, lightDir), 0.0);
        vec3 diffuse = diff * color * attenuation * intensity;

        // specular
        float specularStrength = 0.2f;
        vec3 viewDir = normalize(cameraPosition - vec3(FragPos));
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
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
    vec3 encoded_normal = texture(normalTexture, TexCoord).rgb;
    encoded_normal = 2.0 * encoded_normal - 1.0;    // RGB to vector <0,1> -> <-1,1>
    encoded_normal = normalize(encoded_normal * vec3(1, 1, 5));
    vec3 norm = normalize(tbn * encoded_normal);

    vec4 texcolor = texture(objectTexture, TexCoord);
    if(texcolor.a < 0.1)
        discard;
    frag_colour = texcolor;

    for(int i = 0; i < how_many_lights; i++) {
        lights[i].type == 1 ? (frag_colour = frag_colour + vec4(point_light(lights[i], norm), 1.0f)) : frag_colour;
        lights[i].type == 2 ? (frag_colour = frag_colour + vec4(directional_light(lights[i], norm), 1.0f)) : frag_colour;
        lights[i].type == 3 ? (frag_colour = frag_colour + vec4(spot_light(lights[i], norm), 1.0f)) : frag_colour;
    }
    if (foggy == 1.0f)
    frag_colour = fog(frag_colour);
}
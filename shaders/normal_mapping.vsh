#version 330

layout (location = 0) in vec4 aPos;
layout (location = 1) in vec4 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout(location = 3) in vec3 tangents;
out vec3 ourColor;
out vec3 coordinates;
out vec2 TexCoord;
out vec3 Normal;
out vec4 colors;
out mat3 tbn;
in vec3 worldPosition;
in vec3 worldNormal;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

void main () {
    //Gram-Schmidt orthonormalization -> 3 perpendicular vectors
    vec3 normal = normalize(aNormal.xyz);
    vec3 tangent = normalize(normalize(tangents) - dot(normalize(tangents), normal) * normal);
    vec3 bitangent = cross(normal, tangent);

    // get rid of translation and make sure normal and transform maintain the same orientation
    mat3 normalm = transpose(inverse(mat3(modelMatrix)));

    vec3 T = normalize(vec3(normalm * tangent));
    vec3 B = normalize(vec3(normalm * bitangent));
    vec3 N = normalize(vec3(normalm * normal));
    tbn = mat3(T, B, N);

    gl_Position = projectionMatrix*viewMatrix*modelMatrix*aPos;
    FragPos = vec3(modelMatrix*aPos);
    colors = aNormal;
    Normal = vec3(aNormal);
    ourColor = vec3(aNormal);
    TexCoord.x = aTexCoord.x;
    TexCoord.y = -aTexCoord.y;

}
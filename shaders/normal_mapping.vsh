#version 330

layout (location = 0) in vec4 vertexPosition;
layout (location = 1) in vec4 modelNormals;
layout (location = 2) in vec2 textureCoordinates;
layout(location = 3) in vec3 tangents;
out vec3 coordinates;
out vec2 textureCoordinatesOut;
out vec3 Normal;
out mat3 tbn;
out vec3 FragPos;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main () {
    //Gram-Schmidt orthonormalization -> 3 perpendicular vectors
    vec3 normal = normalize(modelNormals.xyz);
    vec3 tangent = normalize(tangents - dot(tangents, normal) * normal);
    vec3 bitangent = cross(normal, tangent);

    // get rid of translation and make sure normal and transform maintain the same orientation
    mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));

    vec3 T = normalize(vec3(normalMatrix * normalize(tangent)));
    vec3 B = normalize(vec3(normalMatrix * bitangent));
    vec3 N = normalize(vec3(normalMatrix * normal));
    tbn = mat3(T, B, N);

    gl_Position = projectionMatrix*viewMatrix*modelMatrix*vertexPosition;
    FragPos = vec3(modelMatrix* vertexPosition);
    Normal = vec3(normalMatrix*modelNormals.xyz);

    textureCoordinatesOut.x = textureCoordinates.x;
    textureCoordinatesOut.y = -textureCoordinates.y;
}
#version 400

#define M_PI 3.1415926535897932384626433832795

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec4 lightPosition;
uniform bool useTexCoords;

layout (location = 1) in vec4 color;
layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;
layout (location = 3) in vec2 texCoords;

out vec2 fs_texCoords;
out vec4 fragmentColor;
out vec4 normalPosition;
out vec4 worldPosition;
out float vertexDistanceFromLight;

void main() {
    mat4 mvp = proj * view * model;
    gl_Position = mvp * position;
    fragmentColor = color;
    normalPosition = model*normal;
    worldPosition = model*position;

    if(useTexCoords)
        fs_texCoords = texCoords;
    else
        fs_texCoords = position.xz;

    vertexDistanceFromLight = distance(position, lightPosition);
}

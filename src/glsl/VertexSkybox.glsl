#version 400

uniform mat4 proj;
uniform mat4 view;

layout (location = 0) in vec3 position;

out vec3 texCoords;

void main() {
    gl_Position = proj * view  * vec4(position, 1.0);
    texCoords = position;
}

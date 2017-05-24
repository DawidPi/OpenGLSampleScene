#version 400

layout (location=0) in vec3 position;
layout (location=1) in vec2 textureCoords;
out vec2 texCoords;


void main() {
    texCoords = textureCoords;
    gl_Position = vec4(position.x, position.y , position.z, 1.0);
}

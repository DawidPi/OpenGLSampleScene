#version 400

in vec3 texCoords;
out vec4 color;

uniform samplerCube skyboxTexture;

void main() {
    color = texture(skyboxTexture, texCoords);
}

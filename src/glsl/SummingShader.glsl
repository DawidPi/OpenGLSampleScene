#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D cubeTexture;
uniform sampler2D blurredTexture;

void main() {
    clamp(texCoords.x, 0.001, 0.999);
    clamp(texCoords.y, 0.001, 0.999);
    fs_color = texture(cubeTexture, texCoords) + texture(blurredTexture, texCoords);
}

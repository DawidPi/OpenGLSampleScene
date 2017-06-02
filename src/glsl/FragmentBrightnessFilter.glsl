#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D cubeTexture;

void main() {
    vec3 color = texture(cubeTexture, texCoords).rgb;
    fs_color =  vec4(0.75*length(color) * color, 1.0);
}

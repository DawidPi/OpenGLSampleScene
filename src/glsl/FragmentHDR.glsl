#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D hdrTexture;

void main() {
    const float gamma = 2.2;

    vec3 hdrColor = texture(hdrTexture, texCoords).rgb;
    vec3 reinhardMapping = hdrColor/(hdrColor+vec3(1.0));
    reinhardMapping = pow(reinhardMapping, vec3(1.0/gamma));

    fs_color = vec4(reinhardMapping, 1.0);
}

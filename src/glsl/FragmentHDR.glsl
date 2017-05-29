#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D hdrTexture;

void main() {
    const float gamma = 2.2;

    vec3 hdrColor = vec3(texture(hdrTexture, texCoords, 0));
    float exposure = 1.5;
    vec3 exposureMapping = vec3(1.0) - exp(-hdrColor * exposure);
    exposureMapping = pow(exposureMapping, vec3(1.0/gamma));

    fs_color = vec4(exposureMapping, 1.0);
}

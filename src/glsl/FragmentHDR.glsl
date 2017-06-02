#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D hdrTexture;

void main() {
    const float gamma = 2.2;

    clamp(texCoords.x, 0.001, 0.999);
    clamp(texCoords.y, 0.001, 0.999);

    vec3 hdrColor = vec3(texture(hdrTexture, texCoords, 0));
    float exposure = 1.0;
    vec3 exposureMapping = vec3(1.0) - exp(-hdrColor * exposure);
    exposureMapping = pow(exposureMapping, vec3(1.0/gamma));

    fs_color = vec4(exposureMapping, 1.0);
}

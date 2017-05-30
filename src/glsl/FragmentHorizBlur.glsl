#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D cubeTexture;
uniform vec2 screenSize;

void main() {
    float sumWeights = 9.0;
    float[5] weights = float[](1.0/sumWeights, 2.0/sumWeights, 3.0/sumWeights, 2.0/sumWeights, 1.0/sumWeights);

    vec3 outputTexelValue = vec3(0.0);

    for(int vertIdx=0; vertIdx < 5; vertIdx++){
        vec2 textureOffset = vec2(-2.0 + vertIdx, 0.0)/screenSize;
        outputTexelValue += weights[vertIdx] * vec3(texture(cubeTexture, texCoords + textureOffset));
    }

    fs_color = vec4(outputTexelValue, 1.0);
}

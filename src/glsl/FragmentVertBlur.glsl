#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D cubeTexture;
uniform vec2 screenSize;

void main() {
    float sumWeights = 64.0;
    float[7] weights = float[](1.0/sumWeights, 6.0/sumWeights, 15.0/sumWeights, 20.0/sumWeights,
     15.0/sumWeights, 6.0/sumWeights, 1.0/sumWeights);

    vec3 outputTexelValue = vec3(0.0);

    for(int vertIdx=0; vertIdx < 7; vertIdx++){
        vec2 textureOffset = vec2(0.0, -3.0 + vertIdx)/screenSize;
        vec2 finalPosition = texCoords + textureOffset;
        outputTexelValue += weights[vertIdx] * vec3(texture(cubeTexture, finalPosition));
    }

    fs_color = vec4(outputTexelValue, 1.0);
}

#version 400

out vec4 fs_color;
in vec2 texCoords;

uniform sampler2D cubeTexture;

void main() {
    vec3 color = texture(cubeTexture, texCoords).rgb;

    if(length(color) > 0.0){
        fs_color = vec4(color, 1.0);
    } else{
        fs_color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}

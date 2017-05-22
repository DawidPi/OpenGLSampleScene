#version 400

in vec4 fragmentColor;
in vec2 fs_texCoords;
uniform bool useTexture;

uniform sampler2D fs_texture;
out vec4 fs_color;

void main(void)
{
    if(useTexture)
        fs_color = texture(fs_texture, fs_texCoords);
    else{
        fs_color = fragmentColor;
    }
}
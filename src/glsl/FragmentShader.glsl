#version 400

in vec4 fragmentColor;
out vec4 fs_color;

void main(void)
{
    fs_color = fragmentColor;
}
#version 400

#define M_PI 3.1415926535897932384626433832795

uniform mat4 transformation;

void main() {
    gl_Position = transformation*position;
}

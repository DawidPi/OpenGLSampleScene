#version 400

#define M_PI 3.1415926535897932384626433832795

uniform mat4 proj;
uniform mat4 view;
uniform mat4 model;
uniform vec4 lightPosition;
uniform bool useLighting;
uniform bool isLightSource;
uniform vec4 cameraPosition;

layout (location = 1) in vec4 color;
layout (location = 0) in vec4 position;
layout (location = 2) in vec4 normal;

out vec4 fragmentColor;


void main() {
    mat4 mvp = proj * view * model;

    vec4 final_position = mvp * position;
    gl_Position = final_position;

    if(useLighting){
        vec4 normal_position = model*normal;
        float lightingFactor = dot(normalize(lightPosition - (model*position)), normalize(normal_position));

        if(isLightSource){
            float lightingFactor = dot(normalize(cameraPosition - (model*position)), normalize(normal_position));
            fragmentColor = vec4(color.xyz, lightingFactor - 20*(1.0f - lightingFactor));
        } else{
            float lightingFactor = dot(normalize(lightPosition - (model*position)), normalize(normal_position));
            fragmentColor = vec4(color.xyz * lightingFactor, 1.0f);
        }
    } else {
        fragmentColor = color;
    }
}

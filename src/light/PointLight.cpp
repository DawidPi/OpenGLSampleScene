//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include "PointLight.hpp"

PointLight::PointLight(glm::vec3 lightPosition) : mLightPosition(lightPosition) {}

void PointLight::placeLight(GLuint program) {
    auto uniformLocation = glGetUniformLocation(program, "lightPosition");
    glm::vec4 glslLightPosition(mLightPosition, 1.0f);
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(glslLightPosition));
}

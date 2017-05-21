//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include <glad/glad.h>
#include "PointLight.hpp"

PointLight::PointLight() :
        mLightBulb(glm::vec3(1.0f,1.0f,1.0f), .25f, 400, 400) {}

void PointLight::init() {
    mLightBulb.init();
}

void PointLight::placeLight(GLuint program, const glm::vec4 &lightPosition, const glm::vec4 &cameraPosition) {

    mLightPosition = lightPosition;

    auto uniformLocation = glGetUniformLocation(program, "useLighting");
    glUniform1ui(uniformLocation, GL_TRUE);

    uniformLocation = glGetUniformLocation(program, "lightPosition");
    glUniform4fv(uniformLocation, 0, glm::value_ptr(lightPosition));

    uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_FALSE);
}

void PointLight::draw(GLuint program, const glm::vec4 &cameraPosition) {

    auto uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_TRUE);

    mLightBulb.draw(program, glm::translate(glm::mat4(1.0f), glm::vec3(mLightPosition)));

    uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_FALSE);
}

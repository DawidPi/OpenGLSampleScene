//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include <glad/glad.h>
#include "PointLight.hpp"

PointLight::PointLight() :
        mLightBulb(glm::vec3(1.0f, 1.0f, 0.0f), 10.0f, 360, 360) {}

void PointLight::init() {
    mLightBulb.init(0);
}

void PointLight::placeLight(GLuint program, const glm::vec4 &lightPosition) {

    mLightPosition = lightPosition;

    auto uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_FALSE);

    uniformLocation = glGetUniformLocation(program, "lightPosition");
    glUniform4fv(uniformLocation, 1, glm::value_ptr(lightPosition));

    uniformLocation = glGetUniformLocation(program, "lightColor");
    glUniform3fv(uniformLocation, 1, glm::value_ptr(glm::vec3(1.0f,1.0f,1.0f)));
}

void PointLight::draw(GLuint program) {

    auto uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_TRUE);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mLightBulb.draw(program, glm::translate(glm::mat4(1.0f), glm::vec3(mLightPosition)));

    glDisable(GL_BLEND);

    uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_FALSE);
}

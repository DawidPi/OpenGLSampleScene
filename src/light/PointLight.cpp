//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include <glad/glad.h>
#include "PointLight.hpp"

PointLight::PointLight() :
        mLightBulb(10.0f, 360, 360) {}

void PointLight::init(GLuint program) {
    mSunTexture.load("textures/SunTexture.png", program);
    mLightBulb.init();
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

    mLightBulb.draw(program, glm::translate(glm::mat4(1.0f), glm::vec3(mLightPosition)), mSunTexture);

    uniformLocation = glGetUniformLocation(program, "isLightSource");
    glUniform1ui(uniformLocation, GL_FALSE);
}

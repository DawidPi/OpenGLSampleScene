//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include <iostream>
#include "Camera.hpp"

Camera::Camera(const glm::vec3 &cameraPosition, float screenRatio, float rotationX, float rotationY, double zoom ) {

    auto rotationXMatrix = glm::rotate(glm::mat4(1.0f), -rotationX ,glm::vec3(1.0f, 0.0f, 0.0f));
    mProj = glm::perspective(glm::radians(45.0f/(float)zoom), screenRatio, 1.0f, 1000.0f )
                * rotationXMatrix;

    auto rotationYMatrix = glm::rotate(glm::mat4(1.0f), -rotationY ,glm::vec3(0.0f, 1.0f, 0.0f));
    mView = rotationYMatrix *
            glm::lookAt(
            cameraPosition,
            cameraPosition + glm::vec3(0.0f,0.0f,1000.0f),
            glm::vec3(0.0f,1.0f,0.0f)
            );

    mCameraPos = glm::vec4(cameraPosition,1.0f);
    mLookDirection = rotationYMatrix * rotationXMatrix * glm::vec4(cameraPosition + glm::vec3(0.0f,0.0f,1000.0f),1.0f);
    std::cout << glm::to_string(mLookDirection) << std::endl;
}

void Camera::placeCamera(GLuint program) {
    setView(program);
    setProjection(program);
    setCameraPosition(program);
    setLookDirection(program);
}

void Camera::setLookDirection(GLuint program) const {
    auto uniformLocation = glGetUniformLocation(program, "lookDirection");
    glUniform4fv(uniformLocation, 1, value_ptr(mLookDirection));
}

void Camera::setCameraPosition(GLuint program) const {
    auto uniformLocation = glGetUniformLocation(program, "cameraPosition");
    glUniform4fv(uniformLocation, 1, value_ptr(mCameraPos));
}

void Camera::setProjection(GLuint program) const {
    auto uniformLocation = glGetUniformLocation(program, "proj");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mProj));
}

void Camera::setView(GLuint program) const {
    auto uniformLocation = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mView));
}

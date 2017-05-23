//
// Created by dapl on 2017-05-19.
//

#include <glm/ext.hpp>
#include "Camera.hpp"

Camera::Camera(const glm::vec3 &cameraPosition, float screenRatio, float rotationX, float rotationY) {
    auto rotationXMatrix = glm::rotate(glm::mat4(1.0f), -rotationX ,glm::vec3(1.0f, 0.0f, 0.0f));
    mProj = glm::perspective(glm::radians(45.0f), screenRatio, 1.0f, 1000.0f )
                * rotationXMatrix;

    auto rotationYMatrix = glm::rotate(glm::mat4(1.0f), -rotationY ,glm::vec3(0.0f, 1.0f, 0.0f));
    mView = rotationYMatrix *
            glm::lookAt(
            cameraPosition,
            cameraPosition + glm::vec3(0.0f,0.0f,1000.0f),
            glm::vec3(0.0f,1.0f,0.0f)
            );

    mCameraPos = glm::vec4(cameraPosition,1.0f);
    mLookDirection = rotationYMatrix * glm::vec4(cameraPosition + glm::vec3(0.0f,0.0f,1000.0f),1.0f);
}

void Camera::placeCamera(GLuint program) {
    auto uniformLocation = glGetUniformLocation(program, "view");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mView));

    uniformLocation = glGetUniformLocation(program, "proj");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(mProj));

    uniformLocation = glGetUniformLocation(program, "cameraPosition");
    glUniform4fv(uniformLocation, 1, glm::value_ptr(mCameraPos));

    uniformLocation = glGetUniformLocation(program, "lookDirection");
    glUniform4fv(uniformLocation, 1, glm::value_ptr(mLookDirection));
}

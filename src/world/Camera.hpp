//
// Created by dapl on 2017-05-19.
//

#ifndef PROJECT_CAMERA_HPP
#define PROJECT_CAMERA_HPP


#include <glm/vec4.hpp>
#include <glm/matrix.hpp>
#include <glad/glad.h>

class Camera {
public:
    Camera(const glm::vec3 &cameraPosition, float screenRatio, float rotationX, float rotationY);
    void placeCamera(GLuint program);

    void setView(GLuint program) const;

    void setProjection(GLuint program) const;

    void setCameraPosition(GLuint program) const;

    void setLookDirection(GLuint program) const;

private:
    glm::mat4 mProj;
    glm::mat4 mView;
    glm::vec4 mCameraPos;
    glm::vec4 mLookDirection;
};


#endif //PROJECT_CAMERA_HPP

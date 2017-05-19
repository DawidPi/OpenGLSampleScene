//
// Created by dapl on 2017-05-19.
//

#ifndef PROJECT_CAMERA_HPP
#define PROJECT_CAMERA_HPP


#include <glm/vec3.hpp>
#include <glad/glad.h>

class Camera {
public:
    Camera(const glm::vec3 &cameraPosition, float screenRatio, float rotationX, float rotationY);
    void placeCamera(GLuint program);

private:
    glm::mat4 mProj;
    glm::mat4 mView;
};


#endif //PROJECT_CAMERA_HPP

//
// Created by dapl on 2017-05-19.
//

#ifndef PROJECT_POINTLIGHT_HPP
#define PROJECT_POINTLIGHT_HPP


#include <glm/vec3.hpp>
#include <glad/glad.h>

class PointLight {
public:
    PointLight(glm::vec3 lightPosition);
    void placeLight(GLuint program);

private:
    glm::vec3 mLightPosition;
};


#endif //PROJECT_POINTLIGHT_HPP

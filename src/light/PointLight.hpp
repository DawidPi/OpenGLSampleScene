//
// Created by dapl on 2017-05-19.
//

#ifndef PROJECT_POINTLIGHT_HPP
#define PROJECT_POINTLIGHT_HPP


#include <glm/vec3.hpp>
#include <glad/glad.h>
#include <SphereModel.hpp>

class PointLight {
public:
    PointLight();
    void init();
    void placeLight(GLuint program, const glm::vec4 &lightPosition, const glm::vec4 &cameraPosition);
    void draw(GLuint program, const glm::vec4 &cameraPosition);

private:
    SphereModel mLightBulb;
    glm::vec4 mLightPosition;
};


#endif //PROJECT_POINTLIGHT_HPP

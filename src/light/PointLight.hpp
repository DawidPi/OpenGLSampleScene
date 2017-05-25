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
    void init(GLuint program);
    void placeLight(GLuint program, const glm::vec4 &lightPosition);
    void draw(GLuint program);

private:
    SphereModel mLightBulb;
    Texture mSunTexture;
    glm::vec4 mLightPosition;
};


#endif //PROJECT_POINTLIGHT_HPP

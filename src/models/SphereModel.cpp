//
// Created by dapl on 2017-05-19.
//

#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <iostream>
#include "SphereModel.hpp"

SphereModel::SphereModel(const glm::vec3 &color, double radius, unsigned int rows, unsigned int cols) : mColor(color, 1.0f) {
    auto longitudeStep = 2*glm::pi<GLfloat>()/cols;
    auto latitudeStep = 2*glm::pi<GLfloat>()/rows;
    for(float longitude=0.0f; longitude <= 2*glm::pi<GLfloat>(); longitude += longitudeStep){
        for(float latitude =0.0f; latitude <= 2*glm::pi<GLfloat>(); latitude += latitudeStep){
            float x = radius * cos(longitude)*sin(latitude);
            float y = radius * sin(longitude) * sin(latitude);
            float z = radius * cos(latitude);
            mVertices.push_back(glm::vec4(x, y, z, 1.0f));
            mNormals.push_back(glm::vec4(x, y, z, 0.0f));
            mColors.push_back(glm::vec4(color, 1.0f));

            x = radius * cos(longitude)*sin(latitude + latitudeStep);
            y = radius * sin(longitude) * sin(latitude + latitudeStep);
            z = radius * cos(latitude + latitudeStep);
            mVertices.push_back(glm::vec4(x,y,z,1.0f));
            mNormals.push_back(glm::vec4(x, y, z, 0.0f));
            mColors.push_back(glm::vec4(color, 1.0f));
        }
    }

    for(auto elem : mVertices){
        std::cout << glm::to_string(elem) << std::endl;
    }
}

void SphereModel::init() {
    glGenVertexArrays(1, &mVao);

    glBindVertexArray(mVao);

    glGenBuffers(1, &mSphereBuffer);
    glGenBuffers(1, &mSphereColorBuffer);
    glGenBuffers(1, &mSphereNormalsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(glm::vec4), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors().size() * sizeof(glm::vec4), colors().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(glm::vec4), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);
}

std::vector<glm::vec4> &SphereModel::vertices() {
    return mVertices;
}

std::vector<glm::vec4> &SphereModel::colors() {
    return mColors;
}

std::vector<glm::vec4> &SphereModel::normals() {
    return mNormals;
}

void SphereModel::draw(GLuint program, const glm::mat4 &model) {
    glBindVertexArray(mVao);

    glPointSize(2.0f);
    auto uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_POINTS, 0, (GLsizei) (vertices().size() * 4));
}

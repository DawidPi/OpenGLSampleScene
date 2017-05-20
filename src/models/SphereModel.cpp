//
// Created by dapl on 2017-05-19.
//

#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <iostream>
#include "SphereModel.hpp"

SphereModel::SphereModel(const glm::vec3 &color, double radius, unsigned int rows, unsigned int cols) {
    auto colStep = 2*glm::pi<GLfloat>()/cols;
    auto rowStep = 2*glm::pi<GLfloat>()/rows;

    for(float currentRow =0.0f; currentRow <= 2*glm::pi<GLfloat>(); currentRow += rowStep){
        for(float currentCol=0.0f; currentCol <= 2*glm::pi<GLfloat>(); currentCol += colStep){

            GLfloat x = radius*sin(currentRow+rowStep)*cos(currentCol);
            GLfloat y = radius*cos(currentRow+rowStep);
            GLfloat z = radius*sin(currentRow+rowStep)*sin(currentCol);

            mVertices.push_back(x);
            mVertices.push_back(y);
            mVertices.push_back(z);
            mVertices.push_back(1.0f);
            mNormals.push_back(glm::vec4(x,y,z,0.0f));
            mColors.push_back(glm::vec4(color, 1.0f));

            x = radius*sin(currentRow)*cos(currentCol);
            y = radius*cos(currentRow);
            z = radius*sin(currentRow)*sin(currentCol);

            mVertices.push_back(x);
            mVertices.push_back(y);
            mVertices.push_back(z);
            mVertices.push_back(1.0f);
            mNormals.push_back(glm::vec4(x,y,z,0.0f));
            mColors.push_back(glm::vec4(color, 1.0f));
        }
    }
}

void SphereModel::init() {
    glGenVertexArrays(1, &mVao);

    glBindVertexArray(mVao);

    glGenBuffers(1, &mSphereBuffer);
    glGenBuffers(1, &mSphereColorBuffer);
    glGenBuffers(1, &mSphereNormalsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(GLfloat), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors().size() * sizeof(glm::vec4), colors().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1,4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(glm::vec4), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

std::vector<GLfloat> &SphereModel::vertices() {
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

    glCullFace(GL_FRONT);

    auto uniformLocation = glGetUniformLocation(program, "useLighting");
    glUniform1ui(uniformLocation, true);

    uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) (vertices().size()));

    glBindVertexArray(0);
}

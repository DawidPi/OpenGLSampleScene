//
// Created by dapl on 2017-05-12.
//

#include <glm/ext.hpp>
#include "LandModel.hpp"

const std::vector<GLfloat> LandModel::vertexBuffer{
        -10.0f, 0.0f, -10.0f, 1.0f,
        -10.0f, 0.0f, 10.0f, 1.0f,
        10.0f, 0.0f, -10.0f, 1.0f,
        10.0f, 0.0f, 10.0f, 1.0f,
        0.0f, 0.0f, 0.0f, 1.0f
};
const std::vector<GLfloat> LandModel::colorBuffer{
        95.0f/255, 27.0f/255, 3.0f/255, 0,
        95.0f/255, 27.0f/255, 3.0f/255, 0,
        95.0f/255, 27.0f/255, 3.0f/255, 0,
        95.0f/255, 27.0f/255, 3.0f/255, 0,
        95.0f/255, 27.0f/255, 3.0f/255, 0
};
const std::vector<GLuint> LandModel::indicesBuffer{
        0,4,1,
        1,4,3,
        3,4,2,
        2,4,0
};

const std::vector<GLfloat> LandModel::normalsBuffer{
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
};

void LandModel::init() {
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mLandBuffer);
    glGenBuffers(1, &mLandIndices);
    glGenBuffers(1, &mLandColors);
    glGenBuffers(1, &mLandNormals);

    glBindBuffer(GL_ARRAY_BUFFER, mLandBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(GLfloat), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mLandIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices().size() * sizeof(GLuint), indices().data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, mLandColors);
    glBufferData(GL_ARRAY_BUFFER, colors().size() * sizeof(GLfloat), colors().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mLandNormals);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(GLfloat), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void LandModel::draw(GLuint program, const glm::mat4 &model) {
    glBindVertexArray(mVao);

    auto uniformLocation = glGetUniformLocation(program, "useLighting");
    glUniform1ui(uniformLocation, true);

    uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices().size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

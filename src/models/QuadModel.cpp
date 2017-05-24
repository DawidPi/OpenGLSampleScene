//
// Created by dapl on 2017-05-23.
//

#include <vector>
#include <glm/vec3.hpp>
#include "QuadModel.hpp"

void QuadModel::init() {

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mBuffer);
    glGenBuffers(1, &mTexCoordBuffer);

    std::vector<glm::vec3> vertices{
            glm::vec3(-1.0f, -1.0f, 0.0f),
            glm::vec3( 1.0f, -1.0f, 0.0f),
            glm::vec3( 1.0f,  1.0f, 0.0f),

            glm::vec3(-1.0f, 1.0f, 0.0f),
            glm::vec3( -1.0f, -1.0f, 0.0f),
            glm::vec3( 1.0f, 1.0f, 0.0f),
    };

    std::vector<GLfloat> coords{
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,

            0.0, 1.0,
            0.0, 0.0,
            1.0, 1.0,
    };

    mBufferIndices = vertices.size();

    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(decltype(vertices)::value_type), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, mTexCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, coords.size() * sizeof(GLfloat), coords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void QuadModel::draw(GLuint program) {
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, mBufferIndices);
    glBindVertexArray(0);

}

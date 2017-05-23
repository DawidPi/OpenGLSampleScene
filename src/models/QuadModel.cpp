//
// Created by dapl on 2017-05-23.
//

#include <vector>
#include "QuadModel.hpp"

void QuadModel::init() {

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, mBuffer);

    std::vector<GLfloat> vertices{
            -1.0,  -1.0,
            -1.0, 1.0,
            1.0, -1.0,

            -1.0, 1.0,
            1.0, 1.0,
            1.0, -1.0,
    };

    mBufferIndices = vertices.size();

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void QuadModel::draw(GLuint program) {
    glBindVertexArray(mVao);
    glDrawArrays(GL_TRIANGLES, 0, mBufferIndices);
    glBindVertexArray(0);

}

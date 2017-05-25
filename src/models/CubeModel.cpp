//
// Created by dapl on 2017-05-12.
//

#include <glm/mat4x4.hpp>
#include <glm/ext.hpp>
#include "CubeModel.hpp"

CubeModel::CubeModel() : mVao(47){}

void CubeModel::init() {
    glGenVertexArrays(1, &mVao);

    glBindVertexArray(mVao);

    glGenBuffers(1, &mCubeBuffer);
    glGenBuffers(1, &mCubeColorBuffer);
    glGenBuffers(1, &mCubeNormalsBuffer);
    glGenBuffers(1, &mTexCoordsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(GLfloat), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(GLfloat), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER, mTexCoords.size() * sizeof(GLfloat), mTexCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

    glBindVertexArray(0);
}


void CubeModel::draw(GLuint program, const glm::mat4 &model, Texture &texture) {
    glBindVertexArray(mVao);

    auto uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    texture.attach();

    uniformLocation = glGetUniformLocation(program, "useTexCoords");
    glUniform1i(uniformLocation, GL_TRUE);

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertexBufferPrim.size());

    texture.detach();

    uniformLocation = glGetUniformLocation(program, "useTexCoords");
    glUniform1i(uniformLocation, GL_FALSE);

    glBindVertexArray(0);
}


const std::vector<GLfloat> CubeModel::mTexCoords{
        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        1.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        1.0, 0.0,

        0.0, 0.0,
        0.0, 1.0,
        1.0, 1.0,
        0.0, 0.0,
        1.0, 1.0,
        1.0, 0.0,

        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0,
        1.0, 1.0,
        0.0, 0.0,

        1.0, 1.0,
        1.0, 0.0,
        0.0, 1.0,
        1.0, 0.0,
        0.0, 0.0,
        0.0, 1.0,
};

const std::vector<GLfloat> CubeModel::vertexBufferPrim{
        0.5f, 0.5f, 0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        0.5f, 0.5f, -0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,

        0.5f, -0.5f, 0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,

        -0.5f, -0.5f, -0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,

        -0.5f, 0.5f, -0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        0.5f, 0.5f, -0.5f, 1,

        0.5f, 0.5f, 0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,

        0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
};

const std::vector<GLfloat> CubeModel::normalsBuffer{
        1.0f, 0.0f, 0.0f, 0,
        1.0f, 0.0f, 0.0f, 0,
        1.0f, 0.0f, 0.0f, 0,
        1.0f, 0.0f, 0.0f, 0,
        1.0f, 0.0f, 0.0f, 0,
        1.0f, 0.0f, 0.0f, 0,

        0.0f, -1.0f, 0.0f, 0,
        0.0f, -1.0f, 0.0f, 0,
        0.0f, -1.0f, 0.0f, 0,
        0.0f, -1.0f, 0.0f, 0,
        0.0f, -1.0f, 0.0f, 0,
        0.0f, -1.0f, 0.0f, 0,

        -1.0f, 0.0f, 0.0f, 0,
        -1.0f, 0.0f, 0.0f, 0,
        -1.0f, 0.0f, 0.0f, 0,
        -1.0f, 0.0f, 0.0f, 0,
        -1.0f, 0.0f, 0.0f, 0,
        -1.0f, 0.0f, 0.0f, 0,

        0.0f, 1.0f, 0.0f, 0,
        0.0f, 1.0f, 0.0f, 0,
        0.0f, 1.0f, 0.0f, 0,
        0.0f, 1.0f, 0.0f, 0,
        0.0f, 1.0f, 0.0f, 0,
        0.0f, 1.0f, 0.0f, 0,

        0.0f, 0.0f,  1.0f, 0,
        0.0f, 0.0f,  1.0f, 0,
        0.0f, 0.0f,  1.0f, 0,
        0.0f, 0.0f,  1.0f, 0,
        0.0f, 0.0f,  1.0f, 0,
        0.0f, 0.0f,  1.0f, 0,

        0.0f, 0.0f,  -1.0f, 0,
        0.0f, 0.0f,  -1.0f, 0,
        0.0f, 0.0f,  -1.0f, 0,
        0.0f, 0.0f,  -1.0f, 0,
        0.0f, 0.0f,  -1.0f, 0,
        0.0f, 0.0f,  -1.0f, 0,
};


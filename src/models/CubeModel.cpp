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
    glGenBuffers(1, &mCubeIndexBuffer);
    glGenBuffers(1, &mCubeColorBuffer);
    glGenBuffers(1, &mCubeNormalsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(GLfloat), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeColorBuffer);
    glBufferData(GL_ARRAY_BUFFER, colors().size() * sizeof(GLfloat), colors().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(GLfloat), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}


void CubeModel::draw(GLuint program, const glm::mat4 &model) {
    glBindVertexArray(mVao);

    auto uniformLocation = glGetUniformLocation(program, "useLighting");
    glUniform1ui(uniformLocation, true);

    uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    glDrawArrays(GL_TRIANGLES, 0, (GLsizei) vertexBufferPrim.size());
    glBindVertexArray(0);
}

const std::vector<GLfloat> CubeModel::colorBuffer{
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,

        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,

        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,

        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,

        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,

        0.0f, 0.0f, 1.f, 0,
        1.0f, 0.0f, 0.0f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
        0.0f, 1.f, 0.0f, 0,
        0.0f, 0.0f, 1.f, 0,
};


const std::vector<GLfloat> CubeModel::vertexBufferPrim{
        0.5f, 0.5f, 0.5f, 1, //right_begin
        0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        0.5f, -0.5f, -0.5f, 1, //right_end
        0.5f, -0.5f, 0.5f, 1, //bottom_begin
        0.5f, -0.5f, -0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1, //botoom_end
        -0.5f, -0.5f, -0.5f, 1, //left_begin
        -0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1, //left_end
        -0.5f, 0.5f, -0.5f, 1, //top_begin
        -0.5f, 0.5f, 0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        0.5f, 0.5f, 0.5f, 1,
        0.5f, 0.5f, -0.5f, 1, //top_end
        0.5f, 0.5f, 0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1,
        0.5f, -0.5f, 0.5f, 1,
        -0.5f, 0.5f, 0.5f, 1,
        -0.5f, -0.5f, 0.5f, 1, //end
        0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        0.5f, -0.5f, -0.5f, 1,
        -0.5f, 0.5f, -0.5f, 1,
        -0.5f, -0.5f, -0.5f, 1,
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


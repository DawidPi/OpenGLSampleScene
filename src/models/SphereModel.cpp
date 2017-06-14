//
// Created by dapl on 2017-05-19.
//

#include <glm/gtc/constants.hpp>
#include <glad/glad.h>
#include <glm/ext.hpp>
#include <iostream>
#include "SphereModel.hpp"
#include "../Texture.hpp"

SphereModel::SphereModel(double radius, unsigned int rows, unsigned int cols) {
    cols+=2;
    auto colStep = glm::pi<GLfloat>()/(cols);
    auto rowStep = glm::pi<GLfloat>()/rows;

    for(std::size_t currentRow = 0; currentRow < 2*rows; currentRow++){
        for(std::size_t currentCol = 0; currentCol < 2*cols+1; currentCol++){
            float rowValue = currentRow * rowStep;
            float colValue = currentCol * colStep;

            GLfloat x = radius*sin(rowValue+rowStep)*cos(colValue);
            GLfloat y = radius*cos(rowValue+rowStep);
            GLfloat z = radius*sin(rowValue+rowStep)*sin(colValue);

            mVertices.push_back(glm::vec4(x,y,z,1.0f));
            mNormals.push_back(glm::vec4(x,y,z,0.0f));

            x = radius*sin(rowValue)*cos(colValue);
            y = radius*cos(rowValue);
            z = radius*sin(rowValue)*sin(colValue);

            mVertices.push_back(glm::vec4(x,y,z,1.0f));
            mNormals.push_back(glm::vec4(x,y,z,0.0f));

            auto nextTexCoordValueRow = (rowValue + rowStep) / (glm::pi<GLfloat>());
            auto texCoordValueRow = (rowValue) / (glm::pi<GLfloat>());
            auto texCoordValueCol = colValue / (glm::pi<GLfloat>());


            mTexCoords.push_back(glm::vec2(nextTexCoordValueRow, texCoordValueCol));
            mTexCoords.push_back(glm::vec2(texCoordValueRow, texCoordValueCol));
        }

    }

}

void SphereModel::init() {
    glGenVertexArrays(1, &mVao);

    glBindVertexArray(mVao);

    glGenBuffers(1, &mSphereBuffer);
    glGenBuffers(1, &mSphereColorBuffer);
    glGenBuffers(1, &mSphereNormalsBuffer);
    glGenBuffers(1, &mTexCoordsBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(glm::vec4), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0,4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mSphereNormalsBuffer);
    glBufferData(GL_ARRAY_BUFFER, normals().size() * sizeof(glm::vec4), normals().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, mTexCoordsBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 mTexCoords.size() * sizeof(decltype(mTexCoords)::value_type), mTexCoords.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);

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

void SphereModel::draw(GLuint program, const glm::mat4 &model, Texture &texture) {
    glBindVertexArray(mVao);

    auto uniformLocation = glGetUniformLocation(program, "useTexCoords");
    glUniform1i(uniformLocation, GL_TRUE);

    texture.attach();

    uniformLocation = glGetUniformLocation(program, "model");
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(model));

    uniformLocation = glGetUniformLocation(program, "useHalo");
    glUniform1i(uniformLocation, GL_TRUE);

    glPointSize(5.0f);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei) (vertices().size()));

    uniformLocation = glGetUniformLocation(program, "useTexCoords");
    glUniform1i(uniformLocation, GL_FALSE);

    uniformLocation = glGetUniformLocation(program, "useHalo");
    glUniform1i(uniformLocation, GL_FALSE);

    texture.detach();
    glBindVertexArray(0);
}

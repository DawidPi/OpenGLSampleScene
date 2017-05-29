//
// Created by dawid on 24.05.17.
//

#include <glad/glad.h>
#include <vector>
#include <string>
#include <stb_image.h>
#include <glm/detail/type_mat.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "SkyBox.hpp"

const std::vector<GLfloat> SkyBox::mVertices{
        -5.0f,  5.0f, -5.0f,
        -5.0f, -5.0f, -5.0f,
        5.0f, -5.0f, -5.0f,
        5.0f, -5.0f, -5.0f,
        5.0f,  5.0f, -5.0f,
        -5.0f,  5.0f, -5.0f,

        -5.0f, -5.0f,  5.0f,
        -5.0f, -5.0f, -5.0f,
        -5.0f,  5.0f, -5.0f,
        -5.0f,  5.0f, -5.0f,
        -5.0f,  5.0f,  5.0f,
        -5.0f, -5.0f,  5.0f,

        5.0f, -5.0f, -5.0f,
        5.0f, -5.0f,  5.0f,
        5.0f,  5.0f,  5.0f,
        5.0f,  5.0f,  5.0f,
        5.0f,  5.0f, -5.0f,
        5.0f, -5.0f, -5.0f,

        -5.0f, -5.0f,  5.0f,
        -5.0f,  5.0f,  5.0f,
        5.0f,  5.0f,  5.0f,
        5.0f,  5.0f,  5.0f,
        5.0f, -5.0f,  5.0f,
        -5.0f, -5.0f,  5.0f,

        -5.0f,  5.0f, -5.0f,
        5.0f,  5.0f, -5.0f,
        5.0f,  5.0f,  5.0f,
        5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f,  5.0f,
        -5.0f,  5.0f, -5.0f,

        -5.0f, -5.0f, -5.0f,
        -5.0f, -5.0f,  5.0f,
        5.0f, -5.0f, -5.0f,
        5.0f, -5.0f, -5.0f,
        -5.0f, -5.0f,  5.0f,
        5.0f, -5.0f,  5.0f
};

void SkyBox::init(GLuint program) {
    mProgram = program;

    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    glGenBuffers(1, &mCubeBuffer);

    glBindBuffer(GL_ARRAY_BUFFER, mCubeBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices().size() * sizeof(GLfloat), vertices().data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE2);
    glGenTextures(1, &cubeTexture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);

    std::vector<std::string> texturesNames{
            "textures/SkyBox/skyBoxRight.JPG",
            "textures/SkyBox/skyBoxLeft.JPG",
            "textures/SkyBox/skyBoxUp.JPG",
            "textures/SkyBox/skyBoxDown.JPG",
            "textures/SkyBox/skyBoxBack.JPG",
            "textures/SkyBox/skyBoxFront.JPG"
    };

    for(std::size_t textureIdx=0; textureIdx < texturesNames.size(); textureIdx++){
        int width=0;
        int height=0;
        int channels=0;
        auto data = stbi_load(texturesNames[textureIdx].c_str(), &width, &height, &channels, 3);

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + textureIdx,
                     0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

        free(data);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glActiveTexture(GL_TEXTURE0);

    glBindVertexArray(0);
}

void SkyBox::draw(glm::vec3 cameraPosition) {
    glDepthMask(GL_FALSE);
    glBindVertexArray(mVao);

    glBindTexture(GL_TEXTURE_CUBE_MAP, cubeTexture);
    glUniform1i(glGetUniformLocation(mProgram, "skyboxTexture"), 2);


    glDrawArrays(GL_TRIANGLES, 0, vertices().size());
    glBindVertexArray(0);
    glDepthMask(GL_TRUE);
    glActiveTexture(GL_TEXTURE0);
}

const std::vector<GLfloat> &SkyBox::vertices() {
    return mVertices;
}

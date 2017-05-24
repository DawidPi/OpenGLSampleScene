//
// Created by dapl on 2017-05-22.
//

#include "Texture.hpp"
#include "glErrorCheck.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glad/glad.h>

unsigned int Texture::load(std::string path, GLuint glProgram) {
    int width=0;
    int height=0;
    int channels=0;
    mData = stbi_load(path.c_str(), &width, &height, &channels, 3);

    mTextureId = 0;
    mGlProgram = glProgram;
    glGenTextures(1, &mTextureId);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glUniform1i(glGetUniformLocation(glProgram, "fs_texture"), 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, mData);
    glGenerateMipmap(GL_TEXTURE_2D);

    glActiveTexture(GL_TEXTURE0);
    return mTextureId;
}

void Texture::detach() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::attach() {
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glUniform1i(glGetUniformLocation(mGlProgram, "fs_texture"), 1);
    glActiveTexture(GL_TEXTURE0);
}

Texture::~Texture() {
    free(mData);
}

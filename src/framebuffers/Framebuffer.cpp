//
// Created by dapl on 2017-06-02.
//

#include "Framebuffer.hpp"
#include "../glErrorCheck.hpp"

void Framebuffer::init(unsigned int width, unsigned int height, GLuint textureID) {
    mWidth = width;
    mHeight = height;
    mTextureId = textureID;

    glGenFramebuffers(1, &mFramebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    glActiveTexture(mTextureId);
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();

    const GLfloat depthClear= 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &depthClear);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glViewport(0,0, width, height);
}

void Framebuffer::attachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void Framebuffer::detachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::attachTexture(GLint uniformLocation) {
    glActiveTexture(mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glUniform1i(uniformLocation, mTextureId - GL_TEXTURE0);
    glActiveTexture(GL_TEXTURE0);
}

void Framebuffer::castToScreen() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

//
// Created by dapl on 2017-05-30.
//

#include <glad/glad.h>
#include "CasualFramebuffer.hpp"
#include "../glErrorCheck.hpp"

void CasualFramebuffer::init(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mFramebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    glActiveTexture(GL_TEXTURE6);
    glGenTextures(1, &mTexture);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void CasualFramebuffer::attachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void CasualFramebuffer::detachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CasualFramebuffer::attachTexture(GLint uniformLocation) {
    glActiveTexture(GL_TEXTURE6);
    glBindTexture(GL_TEXTURE_2D, mTexture);
    glUniform1i(uniformLocation, 6);
    glActiveTexture(GL_TEXTURE0);
}

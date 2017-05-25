//
// Created by dapl on 2017-05-23.
//

#include <glad/glad.h>
#include <cassert>
#include "HDRFramebuffer.hpp"
#include "../glErrorCheck.hpp"

void HDRFramebuffer::init(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &mTextureId);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0,  GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,mTextureId, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void HDRFramebuffer::attachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void HDRFramebuffer::detachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRFramebuffer::attachTexture(GLuint program) const {
    glUniform1i(glGetUniformLocation(program, "hdrTexture"), 0);
    glBindTexture(GL_TEXTURE_2D, mTextureId);
}

HDRFramebuffer::~HDRFramebuffer() {
    glDeleteFramebuffers(GL_FRAMEBUFFER, &mFramebuffer);
}

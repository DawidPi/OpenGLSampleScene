//
// Created by dapl on 2017-05-23.
//

#include <glad/glad.h>
#include <cassert>
#include "MSAAFramebuffer.hpp"
#include "../glErrorCheck.hpp"

void MSAAFramebuffer::init(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mMSAAFramebuffer);
    glGenFramebuffers(1, &mNoMSAAFramebuffer);

    setUpNoMsaaFramebuffer(width, height);

    glBindFramebuffer(GL_FRAMEBUFFER, mMSAAFramebuffer);

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &mMSAATexture);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, mMSAATexture);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 8, GL_RGBA16F, width, height, GL_TRUE);

    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE ,mMSAATexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void MSAAFramebuffer::setUpNoMsaaFramebuffer(unsigned int width, unsigned int height) {
    glBindFramebuffer(GL_FRAMEBUFFER, mNoMSAAFramebuffer);

    glActiveTexture(GL_TEXTURE4);
    glGenTextures(1, &mNoMSAATexture);
    glBindTexture(GL_TEXTURE_2D, mNoMSAATexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &mDepthFlatBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthFlatBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthFlatBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,mNoMSAATexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void MSAAFramebuffer::attachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mMSAAFramebuffer);
}

void MSAAFramebuffer::detachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void MSAAFramebuffer::attachTexture(GLint uniformLocation) const {
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, mNoMSAATexture);
    glUniform1i(uniformLocation, 4);
    glActiveTexture(GL_TEXTURE0);
}

void MSAAFramebuffer::calculate2DTexture() const {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mMSAAFramebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mNoMSAAFramebuffer);
    glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

MSAAFramebuffer::~MSAAFramebuffer() {
    glDeleteFramebuffers(1, &mMSAAFramebuffer);
    glDeleteTextures(1, &mMSAATexture);
    glDeleteFramebuffers(1, &mNoMSAAFramebuffer);
    glDeleteTextures(1, &mNoMSAATexture);
}

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
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

    glGenRenderbuffers(1, &mDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthBuffer);
    glRenderbufferStorageMultisample(GL_RENDERBUFFER, 8, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE ,mMSAATexture, 0);

    //glBindFramebuffer(GL_FRAMEBUFFER, 0); wtf
    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void HDRFramebuffer::setUpNoMsaaFramebuffer(unsigned int width, unsigned int height) {
    glBindFramebuffer(GL_FRAMEBUFFER, mNoMSAAFramebuffer);

    glActiveTexture(GL_TEXTURE4);
    glGenTextures(1, &mFlatTexture);
    glBindTexture(GL_TEXTURE_2D, mFlatTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    processGLError();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    glGenRenderbuffers(1, &mDepthFlatBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mDepthFlatBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mDepthFlatBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D ,mFlatTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
}

void HDRFramebuffer::attachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, mMSAAFramebuffer);
}

void HDRFramebuffer::detachFramebuffer() const {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void HDRFramebuffer::attachTexture(GLuint program) const {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mMSAAFramebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
//    glBindFramebuffer(GL_READ_FRAMEBUFFER, mMSAAFramebuffer);
//    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mNoMSAAFramebuffer);
//    glBlitFramebuffer(0,0,mWidth,mHeight, 0,0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);

    //glUniform1i(glGetUniformLocation(program, "hdrTexture"), 4);
    //glBindTexture(GL_TEXTURE_2D, mFlatTexture);
}

HDRFramebuffer::~HDRFramebuffer() {
    glDeleteFramebuffers(GL_FRAMEBUFFER, &mMSAAFramebuffer);
    glDeleteFramebuffers(GL_FRAMEBUFFER, &mNoMSAAFramebuffer);
}

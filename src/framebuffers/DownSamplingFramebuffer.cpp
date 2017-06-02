//
// Created by dapl on 2017-05-30.
//

#include "DownSamplingFramebuffer.hpp"
#include "../glErrorCheck.hpp"

void DownSamplingFramebuffer::init(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);

    glActiveTexture(GL_TEXTURE5);
    glGenTextures(1, &mDownsampledTexture);
    glBindTexture(GL_TEXTURE_2D, mDownsampledTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mDownsampledTexture, 0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    processGLFramebufferStatus();
}

void DownSamplingFramebuffer::downSampleFromFramebuffer(GLuint otherFramebufferId, unsigned int otherWidth,
                                                        unsigned int otherHeight) {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, otherFramebufferId);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, mFramebuffer);
    glBlitFramebuffer(0, 0, otherWidth, otherHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DownSamplingFramebuffer::attachTexture(GLint uniformLocation) {
    glActiveTexture(GL_TEXTURE5);
    glBindTexture(GL_TEXTURE_2D, mDownsampledTexture);

    glUniform1i(uniformLocation, 5);
    glActiveTexture(GL_TEXTURE0);
}


DownSamplingFramebuffer::~DownSamplingFramebuffer() {
    glDeleteFramebuffers(1, &mFramebuffer);
    glDeleteTextures(1, &mDownsampledTexture);
}

void DownSamplingFramebuffer::attachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFramebuffer);
}

void DownSamplingFramebuffer::detachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void DownSamplingFramebuffer::castToScreen() {
    glBindFramebuffer(GL_READ_FRAMEBUFFER, mFramebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0,0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}



//
// Created by dapl on 2017-05-30.
//

#include <glad/glad.h>
#include "DoubleFramebuffer.hpp"
#include "../glErrorCheck.hpp"

void DoubleFramebuffer::init(unsigned int width, unsigned int height) {
    mWidth = width;
    mHeight = height;

    glGenFramebuffers(1, &mFirstFramebuffer);

    glBindFramebuffer(GL_FRAMEBUFFER, mFirstFramebuffer);

    glActiveTexture(GL_TEXTURE6);
    glGenTextures(1, &mFirstTexture);
    glBindTexture(GL_TEXTURE_2D, mFirstTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &mFirstDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mFirstDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mFirstDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mFirstTexture, 0);

    glActiveTexture(GL_TEXTURE0);
    processGLFramebufferStatus();
    detachFramebuffer();

    glGenFramebuffers(1, &mSecondFramebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, mSecondFramebuffer);

    glActiveTexture(GL_TEXTURE7);
    glGenTextures(1, &mSecondTexture);
    glBindTexture(GL_TEXTURE_2D, mSecondTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    glGenRenderbuffers(1, &mSecondDepthBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, mSecondDepthBuffer);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, mSecondDepthBuffer);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mSecondTexture, 0);

    glActiveTexture(GL_TEXTURE0);

    processGLFramebufferStatus();

    mCurrentlyUsed = NONE;
}

void DoubleFramebuffer::attachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, mFirstFramebuffer);
    mCurrentlyUsed = FIRST;
}

void DoubleFramebuffer::detachFramebuffer() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    mCurrentlyUsed = NONE;
}

void DoubleFramebuffer::attachTexture(GLint uniformLocation) {
    glActiveTexture(GL_TEXTURE7);
    glBindTexture(GL_TEXTURE_2D, mFirstTexture);
    glUniform1i(uniformLocation, 7);
    glActiveTexture(GL_TEXTURE0);
}

void DoubleFramebuffer::castToScreen() {
    auto framebuffer = (mCurrentlyUsed == FIRST) ? mFirstFramebuffer : mSecondFramebuffer;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, framebuffer);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    glBlitFramebuffer(0, 0, mWidth, mHeight, 0, 0, mWidth, mHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
}

void DoubleFramebuffer::swapFramebuffer() {
    if(mCurrentlyUsed==FIRST){
        glBindFramebuffer(GL_FRAMEBUFFER, mSecondFramebuffer);
        mCurrentlyUsed = SECOND;
    }
    else{
        glBindFramebuffer(GL_FRAMEBUFFER, mFirstFramebuffer);
        mCurrentlyUsed = FIRST;
    }
}

//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_GLERRORCHECK_HPP
#define PROJECT_GLERRORCHECK_HPP

#include <glad/glad.h>
#include <cassert>
#include <iostream>

#define CASE( errorCase ) case errorCase: std::cerr << #errorCase << std::endl; break;

static inline GLenum processGLError() {
    auto error = glGetError();
    switch (error){

        CASE(GL_INVALID_ENUM)

        CASE(GL_INVALID_VALUE)

        CASE(GL_INVALID_OPERATION)

        CASE(GL_INVALID_FRAMEBUFFER_OPERATION)

        CASE(GL_OUT_OF_MEMORY)

        default: std::cerr << "No error recognized" << std::endl;
    }

    return error;
}

static inline GLenum processGLFramebufferStatus(){
    auto error = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    switch (error){
        CASE(GL_FRAMEBUFFER_UNDEFINED)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER)

        CASE(GL_FRAMEBUFFER_UNSUPPORTED)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE)

        CASE(GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS)

        default:
        std::cerr << "No framebuffer error found" << std::endl;
    }

    assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);

    return error;
}

#endif //PROJECT_GLERRORCHECK_HPP

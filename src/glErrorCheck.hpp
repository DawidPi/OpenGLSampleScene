//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_GLERRORCHECK_HPP
#define PROJECT_GLERRORCHECK_HPP

#include <glad/glad.h>
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
#endif //PROJECT_GLERRORCHECK_HPP

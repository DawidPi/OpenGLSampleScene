//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_HDRPROGRAM_HPP
#define PROJECT_HDRPROGRAM_HPP


#include <QuadModel.hpp>
#include "../framebuffers/HDRFramebuffer.hpp"

class HDRProgram {
public:
    void init(const HDRFramebuffer &framebuffer);
    void launch(unsigned int screenWidth, unsigned int screenHeight);

private:
    GLuint mGlProgram;
    GLuint mVertexShader;
    GLuint mFragmentShader;
    QuadModel mModel;

    void createProgramContext();

    void defaultOpenGLSettings() const;

    const HDRFramebuffer *mFramebuffer;
};


#endif //PROJECT_HDRPROGRAM_HPP
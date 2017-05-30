//
// Created by dawid on 23.05.17.
//

#ifndef PROJECT_HDRPROGRAM_HPP
#define PROJECT_HDRPROGRAM_HPP


#include <QuadModel.hpp>
#include "../framebuffers/MSAAFramebuffer.hpp"
#include "../framebuffers/DownSamplingFramebuffer.hpp"

class PostProcessingProgram {
public:
    void init(MSAAFramebuffer& framebuffer, unsigned int width, unsigned int height);
    void start(unsigned int screenWidth, unsigned int screenHeight);
private:
    GLuint mGlHDRProgram;
    GLuint mVertexShader;
    GLuint mFragmentHDRShader;
    GLuint mFragmentVerticalBlurShader;
    GLuint mGlVertBlurProgram;

    QuadModel mModel;

    void createProgramContext();

    void defaultOpenGLSettings() const;
    MSAAFramebuffer * mMSAAFramebuffer;
    DownSamplingFramebuffer mDownSamplingFramebuffer;
};


#endif //PROJECT_HDRPROGRAM_HPP

//
// Created by dawid on 23.05.17.
//

#include <stdexcept>
#include <glm/vec2.hpp>
#include <glm/ext.hpp>
#include "PostProcessingProgram.hpp"
#include "../ShaderNecromanter.hpp"
#include "../glErrorCheck.hpp"

void PostProcessingProgram::init(MSAAFramebuffer& framebuffer, unsigned int width, unsigned int height) {
    createProgramContext();
    mMSAAFramebuffer = &framebuffer;
    mDownSamplingFramebuffer.init(width/2, height/2);
    mModel.init();
}

void PostProcessingProgram::defaultOpenGLSettings() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void PostProcessingProgram::createProgramContext() {
    mGlHDRProgram = glCreateProgram();
    mVertexShader = ShaderNecromanter().spawnShader(GL_VERTEX_SHADER, "glsl/VertexHDR.glsl");
    mFragmentHDRShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentHDR.glsl");
    mFragmentVerticalBlurShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentVertBlur.glsl");
    mFragmentHorizontalBlurShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentHorizBlur.glsl");
    glAttachShader(mGlHDRProgram, mVertexShader);
    glAttachShader(mGlHDRProgram, mFragmentHDRShader);
    glLinkProgram(mGlHDRProgram);

    mGlVertBlurProgram = glCreateProgram();
    glAttachShader(mGlVertBlurProgram, mVertexShader);
    glAttachShader(mGlVertBlurProgram, mFragmentVerticalBlurShader);
    glLinkProgram(mGlVertBlurProgram);

    mGlHorizBlurProgram = glCreateProgram();
    glAttachShader(mGlHorizBlurProgram, mVertexShader);
    glAttachShader(mGlHorizBlurProgram, mFragmentHorizontalBlurShader);
    glLinkProgram(mGlHorizBlurProgram);

    int isLinked = 0;
    glGetProgramiv(mGlHDRProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");

    glGetProgramiv(mGlVertBlurProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");

    glGetProgramiv(mGlHorizBlurProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void PostProcessingProgram::start(unsigned int screenWidth, unsigned int screenHeight) {
    defaultOpenGLSettings();

    glViewport(0,0, screenWidth, screenHeight);
    glUseProgram(mGlVertBlurProgram);

    auto screenSize = glm::vec2((float)screenWidth/2, (float)screenHeight/2);
    glUniform2fv(glGetUniformLocation(mGlVertBlurProgram, "screenSize"), 1, glm::value_ptr(screenSize));

    mMSAAFramebuffer->calculate2DTexture();
    GLint uniformLocation = glGetUniformLocation(mGlVertBlurProgram, "cubeTexture");
    assert(uniformLocation != -1);
    mDownSamplingFramebuffer.downSampleFromFramebuffer(mMSAAFramebuffer->noMSAAID(), screenWidth, screenHeight);
    mDownSamplingFramebuffer.attachTexture(glGetUniformLocation(mGlVertBlurProgram, "cubeTexture"));
    mModel.draw();
}

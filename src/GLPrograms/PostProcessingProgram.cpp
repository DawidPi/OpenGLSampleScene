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
    mDoubleLowResFramebuffer.init(width/2, height/2);
    fullFramebuffer.init(width, height, GL_TEXTURE0+8);
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
    mFragmentBrightnessFilter = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentBrightnessFilter.glsl");
    mFragmentSummingShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/SummingShader.glsl");

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

    mGlBrightnessFilterProgram = glCreateProgram();
    glAttachShader(mGlBrightnessFilterProgram, mVertexShader);
    glAttachShader(mGlBrightnessFilterProgram, mFragmentBrightnessFilter);
    glLinkProgram(mGlBrightnessFilterProgram);

    mSummingProgram = glCreateProgram();
    glAttachShader(mSummingProgram, mVertexShader);
    glAttachShader(mSummingProgram, mFragmentSummingShader);
    glLinkProgram(mSummingProgram);

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

    glGetProgramiv(mGlBrightnessFilterProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");

    glGetProgramiv(mSummingProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void PostProcessingProgram::start(unsigned int screenWidth, unsigned int screenHeight) {
    defaultOpenGLSettings();
    glViewport(0,0, screenWidth/2, screenHeight/2);

    glUseProgram(mGlBrightnessFilterProgram);
    mMSAAFramebuffer->calculate2DTexture();
    mDownSamplingFramebuffer.downSampleFromFramebuffer(mMSAAFramebuffer->noMSAAID(), screenWidth, screenHeight);
    mDoubleLowResFramebuffer.attachFramebuffer();
    mDownSamplingFramebuffer.attachTexture(glGetUniformLocation(mGlBrightnessFilterProgram, "cubeTexture"));
    mModel.draw();

    glUseProgram(mGlVertBlurProgram);
    auto screenSize = glm::vec2((float)screenWidth/2, (float)screenHeight/2);
    glUniform2fv(glGetUniformLocation(mGlVertBlurProgram, "screenSize"), 1, glm::value_ptr(screenSize));

    mDoubleLowResFramebuffer.attachTexture(glGetUniformLocation(mGlVertBlurProgram, "cubeTexture"));
    mDoubleLowResFramebuffer.swapFramebuffer();
    mModel.draw();

    glUseProgram(mGlHorizBlurProgram);
    mDoubleLowResFramebuffer.swapTexture(glGetUniformLocation(mGlHorizBlurProgram, "cubeTexture"));
    mDoubleLowResFramebuffer.swapFramebuffer();

    glUniform2fv(glGetUniformLocation(mGlHorizBlurProgram, "screenSize"), 1, glm::value_ptr(screenSize));
    mModel.draw();

    glUseProgram(mSummingProgram);
    glViewport(0,0,screenWidth, screenHeight);
    mDoubleLowResFramebuffer.swapTexture(glGetUniformLocation(mSummingProgram, "blurredTexture"));
    mDoubleLowResFramebuffer.detachFramebuffer();
    mMSAAFramebuffer->attachTexture(glGetUniformLocation(mSummingProgram, "cubeTexture"));
    fullFramebuffer.attachFramebuffer();
    mModel.draw();


    glUseProgram(mGlHDRProgram);
    fullFramebuffer.attachTexture(glGetUniformLocation(mGlHDRProgram, "hdrTexture"));
    fullFramebuffer.detachFramebuffer();
    mModel.draw();

}

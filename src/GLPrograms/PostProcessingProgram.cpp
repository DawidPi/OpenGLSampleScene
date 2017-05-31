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
    mCasualFramebuffer.init(width, height);
    mCasualFramebuffer.attachFramebuffer();
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
}

void PostProcessingProgram::start(unsigned int screenWidth, unsigned int screenHeight) {
    defaultOpenGLSettings();
    glViewport(0,0, screenWidth, screenHeight);

//    glUseProgram(mGlBrightnessFilterProgram);
    mMSAAFramebuffer->calculate2DTexture();
    mDownSamplingFramebuffer.downSampleFromFramebuffer(mMSAAFramebuffer->noMSAAID(), screenWidth, screenHeight);
//    mDownSamplingFramebuffer.castToScreen();
//    mDownSamplingFramebuffer.attachTexture(glGetUniformLocation(mGlVertBlurProgram, "cubeTexture"));
//    mCasualFramebuffer.attachFramebuffer();
//    mModel.draw();
//    mCasualFramebuffer.castToScreen();

    glViewport(0,0, screenWidth, screenHeight);
    glUseProgram(mGlVertBlurProgram);
    auto screenSize = glm::vec2((float)screenWidth/2, (float)screenHeight/2);
    glUniform2fv(glGetUniformLocation(mGlVertBlurProgram, "screenSize"), 1, glm::value_ptr(screenSize));


    mDownSamplingFramebuffer.attachTexture(glGetUniformLocation(mGlVertBlurProgram, "cubeTexture"));
    mCasualFramebuffer.attachFramebuffer();
    mModel.draw();
    mCasualFramebuffer.detachFramebuffer();

    glUseProgram(mGlHorizBlurProgram);
    mCasualFramebuffer.swapFramebuffer();

    glUniform2fv(glGetUniformLocation(mGlHorizBlurProgram, "screenSize"), 1, glm::value_ptr(screenSize));
    mCasualFramebuffer.attachTexture(glGetUniformLocation(mGlHorizBlurProgram, "cubeTexture"));
    mModel.draw();
    mCasualFramebuffer.castToScreen();
}

//
// Created by dawid on 23.05.17.
//

#include <stdexcept>
#include "HDRProgram.hpp"
#include "../ShaderNecromanter.hpp"

void HDRProgram::init(const HDRFramebuffer &framebuffer) {
    createProgramContext();
    mFramebuffer = &framebuffer;
    mModel.init();
}

void HDRProgram::defaultOpenGLSettings() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void HDRProgram::createProgramContext() {
    mGlProgram = glCreateProgram();
    mVertexShader = ShaderNecromanter().spawnShader(GL_VERTEX_SHADER, "glsl/VertexHDR.glsl");
    mFragmentShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentHDR.glsl");
    glAttachShader(mGlProgram, mVertexShader);
    glAttachShader(mGlProgram, mFragmentShader);
    glLinkProgram(mGlProgram);

    int isLinked = 0;
    glGetProgramiv(mGlProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void HDRProgram::launch(unsigned int screenWidth, unsigned int screenHeight) {
    defaultOpenGLSettings();
//    glClear(GL_COLOR_BUFFER_BIT);
//    const GLfloat depthClear= 1.0f;
//    glClearBufferfv(GL_DEPTH, 0, &depthClear);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//    glViewport(0,0, screenWidth, screenHeight);
    glUseProgram(mGlProgram);
//    glClear(GL_COLOR_BUFFER_BIT);

    mFramebuffer->attachTexture();
    mModel.draw(mGlProgram);
}

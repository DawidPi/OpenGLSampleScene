//
// Created by dapl on 2017-05-23.
//

#include <stdexcept>
#include "HDRProgram.hpp"
#include "../ShaderNecromanter.hpp"

void HDRProgram::init(const HDRFramebuffer &framebuffer) {
    createProgramContext();
    defaultOpenGLSettings();
    mFramebuffer = &framebuffer;
    mModel.init();
}

void HDRProgram::defaultOpenGLSettings() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
}

void HDRProgram::createProgramContext() {
    mGlProgram = glCreateProgram();
    mVertexShader = ShaderNecromanter().spawnShader(GL_VERTEX_SHADER, "glsl/VertexHDR.glsl");
    mFragmentShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentHDR.glsl");
    glAttachShader(mGlProgram, mVertexShader);
    glAttachShader(mGlProgram, mFragmentShader);
    glLinkProgram(mGlProgram);
    glUseProgram(mGlProgram);

    int isLinked = 0;
    glGetProgramiv(mGlProgram, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void HDRProgram::launch(unsigned int screenWidth, unsigned int screenHeight) {
    glUseProgram(mGlProgram);

    glClear(GL_COLOR_BUFFER_BIT);
    const GLfloat depthClear= 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &depthClear);
    glClearColor(0.0f, 0.0f, 5.0f, 0.0f);

    glViewport(0,0, screenWidth, screenHeight);

    mFramebuffer->attachTexture();
    mModel.draw(mGlProgram);
}

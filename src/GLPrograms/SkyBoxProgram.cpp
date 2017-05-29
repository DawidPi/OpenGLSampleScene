//
// Created by dapl on 2017-05-25.
//

#include <stdexcept>
#include "SkyBoxProgram.hpp"
#include "../ShaderNecromanter.hpp"
#include "../world/Camera.hpp"

void SkyBoxProgram::init() {
    createProgramContext();
    mSkyBox.init(mGLProgram);
}

void SkyBoxProgram::createProgramContext() {
    mGLProgram = glCreateProgram();
    mVertexSahder = ShaderNecromanter().spawnShader(GL_VERTEX_SHADER, "glsl/VertexSkybox.glsl");
    mFragmentShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentSkybox.glsl");
    glAttachShader(mGLProgram, mVertexSahder);
    glAttachShader(mGLProgram, mFragmentShader);
    glLinkProgram(mGLProgram);

    int isLinked = 0;
    glGetProgramiv(mGLProgram, GL_LINK_STATUS, &isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void
SkyBoxProgram::start(GLFWwindow *window, const glm::vec3 &position, float rotationX, float rotationY,
                     HDRFramebuffer &framebuffer) {

    const GLfloat depthClear= 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &depthClear);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    int screenWidth = 0;
    int screenHeight = 0;
    glfwGetWindowSize(window, &screenWidth, &screenHeight);
    
    glViewport(0,0, screenWidth, screenHeight);
    glUseProgram(mGLProgram);

    //framebuffer.attachFramebuffer();

    glClear(GL_COLOR_BUFFER_BIT);

    if(screenHeight==0){
        screenHeight=1;
        screenWidth=1;
    }
    Camera camera(glm::vec3(0.0, 0.0, 0.0), (float)screenWidth/screenHeight, rotationX, rotationY);

    camera.setView(mGLProgram);
    camera.setProjection(mGLProgram);

    mSkyBox.draw(glm::vec3(position));

    //framebuffer.detachFramebuffer();
}


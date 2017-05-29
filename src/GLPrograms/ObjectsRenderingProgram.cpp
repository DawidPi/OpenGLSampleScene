//
// Created by dawid on 24.05.17.
//

#include <glad/glad.h>
#include <stdexcept>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include "ObjectsRenderingProgram.hpp"
#include "../ShaderNecromanter.hpp"
#include "../framebuffers/HDRFramebuffer.hpp"
#include "../world/Camera.hpp"
#include "../glErrorCheck.hpp"

void ObjectsRenderingProgram::init() {
    createOpenGLProgram();
    openGLCommonSettings();
    mCube.init();
    mSphere.init();
    mLightSource.init(mGlProgram);
    mLand.init(mGlProgram);
    metalTexture.load("textures/MetalCubeTexture.jpg", mGlProgram);
    jeansTexture.load("textures/jeansTexture.jpg", mGlProgram);
}

void ObjectsRenderingProgram::createOpenGLProgram() {
    mGlProgram = glCreateProgram();
    mVertexShader = ShaderNecromanter().spawnShader(GL_VERTEX_SHADER, "glsl/VertexShader.glsl");
    mFragmentShader = ShaderNecromanter().spawnShader(GL_FRAGMENT_SHADER, "glsl/FragmentShader.glsl");
    glAttachShader(mGlProgram, mVertexShader);
    glAttachShader(mGlProgram, mFragmentShader);
    glLinkProgram(mGlProgram);
    glUseProgram(mGlProgram);

    int isLinked = 0;
    glGetProgramiv(mGlProgram, GL_LINK_STATUS, (int *)&isLinked);
    if(isLinked == GL_FALSE)
        throw std::runtime_error("OpenGL could not link");
}

void ObjectsRenderingProgram::openGLCommonSettings() {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void ObjectsRenderingProgram::clearWindow() const {
    //glClear(GL_COLOR_BUFFER_BIT);
    const GLfloat depthClear= 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &depthClear);
}

void ObjectsRenderingProgram::draw(const HDRFramebuffer &framebuffer, GLFWwindow *window, const glm::vec3 &position,
                                   float rotationX, float rotationY, float timeDiff) {
    clearWindow();
    setUpViewport(window);

    glUseProgram(mGlProgram);
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);

    framebuffer.attachFramebuffer();

    glClear(GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);

    if(width==0){
        width=1;
        height=1;
    }
    Camera camera(position, static_cast<float>(width)/height, rotationX, rotationY);
    camera.placeCamera(mGlProgram);

    glm::mat4 lightModel(1.0f);
    lightModel = glm::rotate(lightModel, glm::radians(-45.0f - 180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lightModel = glm::translate(lightModel, glm::vec3(0.0f, 250.0f, 400.0f));
    lightModel = glm::rotate(lightModel, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));

    mLightSource.placeLight(mGlProgram, glm::vec4(lightModel[3]));

    mCube.draw(mGlProgram, glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 1.00, 2.0f)), metalTexture);
    mCube.draw(mGlProgram, rightCubeModel(timeDiff), metalTexture);
    mCube.draw(mGlProgram, leftCubeModel(timeDiff), metalTexture);
    mLand.draw(mGlProgram, landModel());
    mSphere.draw(mGlProgram, sphereModel(timeDiff), jeansTexture);
    mSphere.draw(mGlProgram, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f)), jeansTexture);
    mLightSource.draw(mGlProgram);

    framebuffer.detachFramebuffer();

}

void ObjectsRenderingProgram::setUpViewport(GLFWwindow *pWwindow) {
    int width = 0;
    int height = 0;
    glfwGetWindowSize(pWwindow, &width, &height);

    glViewport(0,0,width, height);
}

glm::mat4 ObjectsRenderingProgram::rightCubeModel(float timeDiff) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(5.0f, 5.0f, 25.0f));
    model = glm::rotate(model, timeDiff, glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}

glm::mat4 ObjectsRenderingProgram::leftCubeModel(float timeDiff) {
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 5.0f, 25.0f));
    model  = glm::rotate(model, -timeDiff, glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}

glm::mat4 ObjectsRenderingProgram::landModel() {
    auto landModel = glm::mat4(1.0f);
    landModel = glm::scale(landModel, glm::vec3(10.0f, 10.0f, 10.0f));
    landModel = glm::translate(landModel, glm::vec3(0.0f, -1.0f, 0.0f));
    return landModel;
}

glm::mat4 ObjectsRenderingProgram::sphereModel(float timeDiff) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 25.0f));
    model = glm::rotate(model, timeDiff, glm::vec3(0.0f,1.0f,0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 10.0f, 10.0f));
    return model;
}


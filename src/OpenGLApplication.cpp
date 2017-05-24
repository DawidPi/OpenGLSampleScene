//
// Created by dapl on 2017-05-11.
//

#include <glad/glad.h>
#include <vector>
#include <glm/vec4.hpp>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/ext.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "OpenGLApplication.hpp"
#include "ShaderNecromanter.hpp"
#include "world/Camera.hpp"
#include "light/PointLight.hpp"
#include "glErrorCheck.hpp"

void OpenGLApplication::init(unsigned int width, unsigned int height) {
    createOpenGLProgram();
    openGLCommonSettings();
    mCube.init();
    mSphere.init(mGlProgram);
    mLightSource.init();

    mQuadModel.init();
    mHDRFramebuffer.init(width, height);
    mHDRProgram.init(mHDRFramebuffer);
    mLand.init(mGlProgram);

    mTime = std::chrono::system_clock::now();
}

void OpenGLApplication::openGLCommonSettings() const {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void OpenGLApplication::createOpenGLProgram() {
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

void OpenGLApplication::render(GLFWwindow *window) {
    clearWindow();
    setUpViewport(window);

    processButtons();

    glUseProgram(mGlProgram);

    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    mHDRFramebuffer.attachFramebuffer();
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // We're not using stencil buffer now
    glEnable(GL_DEPTH_TEST);
    glm::vec3 position = currentPosition();
    Camera camera(position, static_cast<float>(getWidth())/getHeight(), mRotationX, mRotationY);
    camera.placeCamera(mGlProgram);

    glm::mat4 lightModel(1.0f);
    lightModel = glm::rotate(lightModel, glm::radians(-45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    lightModel = glm::rotate(lightModel, 0.5f*timeDiff(), glm::vec3(1.0f, 0.0f, 0.0f));
    lightModel = glm::translate(lightModel, glm::vec3(0.0f, 0.0f, 200.0f));

    mLightSource.placeLight(mGlProgram, glm::vec4(lightModel[3]));

    mCube.draw(mGlProgram, rightCubeModel());
    mCube.draw(mGlProgram, leftCubeModel());
    mLand.draw(mGlProgram, landModel());
    mSphere.draw(mGlProgram, sphereModel());
    mSphere.draw(mGlProgram, glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
    mLightSource.draw(mGlProgram);

    mHDRFramebuffer.detachFramebuffer();
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    mHDRProgram.launch(width, height);

}

glm::vec3 OpenGLApplication::currentPosition() {
    auto newTranslationZ = mStepper.getCurrentPosition().second;
    auto newTranslationX = mStepper.getCurrentPosition().first;
    auto position = glm::vec3(newTranslationX, 0.0f, newTranslationZ);
    return position;
}

glm::mat4 OpenGLApplication::landModel() const {
    auto landModel = glm::mat4(1.0f);
    landModel = glm::scale(landModel, glm::vec3(10.0f, 10.0f, 10.0f));
    landModel = glm::translate(landModel, glm::vec3(0.0f, -1.0f, 0.0f));
    return landModel;
}

glm::mat4 OpenGLApplication::leftCubeModel() {
    auto model = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, 5.0f, 25.0f));
    model  = glm::rotate(model, -timeDiff(), glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}


glm::mat4 OpenGLApplication::rightCubeModel() const {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(5.0f, 5.0f, 25.0f));
    model = glm::rotate(model, timeDiff(), glm::vec3(0.0f, 1.0f, 0.0f));
    return model;
}

glm::mat4 OpenGLApplication::sphereModel() {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 25.0f));
    model = glm::rotate(model, timeDiff(), glm::vec3(0.0f,1.0f,0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 10.0f, 10.0f));
    return model;
}

float OpenGLApplication::timeDiff() const {
    auto timeDiff = std::chrono::_V2::system_clock::now() - mTime;
    auto timeDiffFloat = std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count() / 1000.0f;
    return timeDiffFloat;
}

void OpenGLApplication::setUpViewport(const GLFWwindow *window) const {
    int width = 0;
    int height = 0;
    glfwGetWindowSize(window, &width, &height);
    glViewport(0,0,width, height);
}

void OpenGLApplication::clearWindow() const {
    glClear(GL_COLOR_BUFFER_BIT);
    const GLfloat depthClear= 1.0f;
    glClearBufferfv(GL_DEPTH, 0, &depthClear);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void OpenGLApplication::processButtons() {
    const auto step=.2f;
    float stepZ=0.0f;
    float stepX=0.0f;
    bool updateStep = false;

    if(mMoveForward){
        stepZ += cos(mRotationY) * step;
        stepX += sin(mRotationY) * step;
        updateStep=true;
    }
    if(mMoveBackwards){
        stepZ += -cos(mRotationY) * step;
        stepX += -sin(mRotationY) * step;
        updateStep=true;
    }

    if(mMoveRight){
        stepZ += sin(mRotationY) * step;
        stepX += -cos(mRotationY) * step;
        updateStep=true;
    }

    if(mMoveLeft){
        stepZ += -sin(mRotationY) * step;
        stepX += cos(mRotationY) * step;
        updateStep=true;
    }

    if(updateStep)
        mStepper.makeStep(stepX, stepZ);
}

void OpenGLApplication::onKey(int key, int, int action, int ) {
    if(key==GLFW_KEY_ESCAPE)
        shutDown();

    const auto actionPressed = action == GLFW_PRESS or action == GLFW_REPEAT;
    const auto actionReleased = action == GLFW_RELEASE;

    if(key == GLFW_KEY_W){
        if(actionPressed){
            mMoveForward = true;
            mMoveBackwards = false;
        }
        else if(actionReleased){
            mMoveForward=false;
        }
    }

    if(key == GLFW_KEY_S){
        if(actionPressed){
            mMoveBackwards = true;
            mMoveForward = false;
        }
        else if(actionReleased){
            mMoveBackwards = false;
        }
    }

    if(key == GLFW_KEY_A){
        if(actionPressed){
            mMoveLeft = true;
            mMoveRight = false;
        }
        else if(actionReleased){
            mMoveLeft = false;
        }
    }

    if(key == GLFW_KEY_D){
        if(actionPressed){
            mMoveRight = true;
            mMoveLeft = false;
        }
        else if(actionReleased){
            mMoveRight = false;
        }
    }
}

void OpenGLApplication::onScroll(double, double) {

}

void OpenGLApplication::onMouseButton(int button, int action, int) {
    if(button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS)
            mMouseButtonPressed=true;
        else if(action == GLFW_RELEASE)
            mMouseButtonPressed=false;
    }
}

void OpenGLApplication::onCursorPositionChanged(double xPosition, double yPosition) {
    MousePosition currentMousePosition(xPosition, yPosition);

    if(mMouseButtonPressed){
        const double scale=0.0005;
        mRotationY -= scale*(mMouseCursorPosition.xPosition - currentMousePosition.xPosition);
        mRotationX -= scale*(mMouseCursorPosition.yPosition - currentMousePosition.yPosition);
    }

    mMouseCursorPosition = currentMousePosition;
}


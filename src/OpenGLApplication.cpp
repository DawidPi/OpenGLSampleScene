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
    mObjectsProgram.init();
    mSkyBoxProgram.init();
    mQuadModel.init();
    mHDRFramebuffer.init(width, height);
    mHDRProgram.init(mHDRFramebuffer);

    mTime = std::chrono::system_clock::now();
}

void OpenGLApplication::render(GLFWwindow *window) {
    processButtons();
    mSkyBoxProgram.start(window, currentPosition(), mRotationX, mRotationY, mHDRFramebuffer, zoom);
    mObjectsProgram.draw(mHDRFramebuffer, window, currentPosition(), mRotationX, mRotationY, timeDiff(), zoom);

    mHDRProgram.start(getWidth(), getHeight());
}

glm::vec3 OpenGLApplication::currentPosition() {
    auto newTranslationZ = mStepper.getCurrentPosition().second;
    auto newTranslationX = mStepper.getCurrentPosition().first;
    auto position = glm::vec3(newTranslationX, 0.0f, newTranslationZ);
    return position;
}


float OpenGLApplication::timeDiff() const {
    auto timeDiff = std::chrono::_V2::system_clock::now() - mTime;
    auto timeDiffFloat = std::chrono::duration_cast<std::chrono::milliseconds>(timeDiff).count() / 1000.0f;
    return timeDiffFloat;
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

    if(updateStep){
        mStepper.makeStep(stepX, stepZ);
    }
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

void OpenGLApplication::onScroll(double xOffset, double yOffset) {
    std::cout << "yOffset: " << yOffset << std::endl;
    if(yOffset > 0.1){
        if(zoom < 50)
            zoom *= 2;
    }else if (yOffset < 0.1){
        if(zoom > 0.5)
            zoom /= 2;
    }
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
        const double scale=0.0008;
        mRotationY -= scale*(mMouseCursorPosition.xPosition - currentMousePosition.xPosition);
        mRotationX -= scale*(mMouseCursorPosition.yPosition - currentMousePosition.yPosition);
    }

    mMouseCursorPosition = currentMousePosition;
}


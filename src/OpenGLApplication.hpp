//
// Created by dapl on 2017-05-11.
//

#ifndef PROJECT_OPENGLAPPLICATION_HPP
#define PROJECT_OPENGLAPPLICATION_HPP


#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x2.hpp>
#include <chrono>
#include <CubeModel.hpp>
#include <LandModel.hpp>
#include <SphereModel.hpp>
#include <QuadModel.hpp>
#include <SkyBox.hpp>
#include "OpenGLWindow.hpp"
#include "Stepper.hpp"
#include "light/PointLight.hpp"
#include "framebuffers/MSAAFramebuffer.hpp"
#include "GLPrograms/PostProcessingProgram.hpp"
#include "GLPrograms/ObjectsRenderingProgram.hpp"
#include "GLPrograms/SkyBoxProgram.hpp"

class OpenGLApplication : public OpenGLWindow {
public:
    OpenGLApplication() :
            mMouseCursorPosition(0,0),
            mStepper(0, 0) {}

    void init(unsigned int width, unsigned int height) override;

    void render(GLFWwindow *window) override;

    void onKey(int key, int scancode, int action, int mods) override;

    void onScroll(double xOffset, double yOffset) override;

    void onMouseButton(int button, int action, int mods) override;

    void onCursorPositionChanged(double xPosition, double yPosition) override;

private:

    struct MousePosition{
        MousePosition(double xPosition_, double yPosition_) : xPosition(xPosition_), yPosition(yPosition_){}
        double xPosition;
        double yPosition;
    };


    bool mMouseButtonPressed=false;
    MousePosition mMouseCursorPosition;
    float mRotationY=0.0;
    float mRotationX=0.0;
    double zoom=1.0;

    std::chrono::system_clock::time_point mTime;

    float timeDiff() const;

    Stepper mStepper;
    bool mMoveForward=false;
    bool mMoveBackwards=false;

    void processButtons();

    bool mMoveLeft=false;
    bool mMoveRight=false;

    glm::vec3 currentPosition();

    MSAAFramebuffer mHDRFramebuffer;
    PostProcessingProgram mHDRProgram;
    QuadModel mQuadModel;

    ObjectsRenderingProgram mObjectsProgram;
    SkyBoxProgram mSkyBoxProgram;
};


#endif //PROJECT_OPENGLAPPLICATION_HPP

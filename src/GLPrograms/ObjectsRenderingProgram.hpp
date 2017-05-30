//
// Created by dawid on 24.05.17.
//

#ifndef PROJECT_OBJECTSRENDERINGPROGRAM_HPP
#define PROJECT_OBJECTSRENDERINGPROGRAM_HPP


#include <CubeModel.hpp>
#include <SphereModel.hpp>
#include <LandModel.hpp>
#include <SkyBox.hpp>
#include "../light/PointLight.hpp"
#include "../framebuffers/MSAAFramebuffer.hpp"
#include "../Stepper.hpp"

class ObjectsRenderingProgram {
public:
    ObjectsRenderingProgram(): mSphere(1.0f, 50, 50) {}
    void init();
    void draw(const MSAAFramebuffer &framebuffer, GLFWwindow *window, const glm::vec3 &position,
                  float rotationX, float rotationY, float timeDiff, double zoom);

private:
    void createOpenGLProgram();
    GLuint mGlProgram;
    GLuint mVertexShader;
    GLuint mFragmentShader;

    void openGLCommonSettings();

    CubeModel mCube;
    SphereModel mSphere;
    PointLight mLightSource;
    LandModel mLand;

    void clearWindow() const;

    void setUpViewport(GLFWwindow *pWwindow);

    glm::mat4 rightCubeModel(float d);

    glm::mat4 leftCubeModel(float d);

    glm::mat4 landModel();

    glm::mat4 sphereModel(float timeDiff);

    Texture metalTexture;
    Texture iceTexture;
};


#endif //PROJECT_OBJECTSRENDERINGPROGRAM_HPP

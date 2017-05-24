//
// Created by dawid on 24.05.17.
//

#ifndef PROJECT_OBJECTSRENDERINGPROGRAM_HPP
#define PROJECT_OBJECTSRENDERINGPROGRAM_HPP


#include <CubeModel.hpp>
#include <SphereModel.hpp>
#include <LandModel.hpp>
#include "../light/PointLight.hpp"
#include "../framebuffers/HDRFramebuffer.hpp"
#include "../StepperInterploator.hpp"

class ObjectsRenderingProgram {
public:
    ObjectsRenderingProgram():mSphere(glm::vec3(1.0f, 1.0f, 1.0f), 1.0f, 50, 50){}
    void init();
    void draw(const HDRFramebuffer &framebuffer, GLFWwindow *window, const glm::vec3 &position,
                  float rotationX, float rotationY, float timeDiff);

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
};


#endif //PROJECT_OBJECTSRENDERINGPROGRAM_HPP

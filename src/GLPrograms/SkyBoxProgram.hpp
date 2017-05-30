//
// Created by dapl on 2017-05-25.
//

#ifndef PROJECT_SKYBOXPROGRAM_HPP
#define PROJECT_SKYBOXPROGRAM_HPP


#include <SkyBox.hpp>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include "../framebuffers/MSAAFramebuffer.hpp"

class SkyBoxProgram {
public:
    void init();
    void start(GLFWwindow *window, const glm::vec3 &position, float rotationX, float rotationY,
                   MSAAFramebuffer &framebuffer, double zoom);

private:
    GLuint mGLProgram;
    GLuint mVertexSahder;
    GLuint mFragmentShader;

    void createProgramContext();

    const MSAAFramebuffer *mFramebuffer;
    SkyBox mSkyBox;
};


#endif //PROJECT_SKYBOXPROGRAM_HPP

//
// Created by dawid on 24.05.17.
//

#ifndef PROJECT_SKYBOX_HPP
#define PROJECT_SKYBOX_HPP

#include <glad/glad.h>
#include <vector>
#include <glm/vec3.hpp>

class SkyBox {
public:
    void init(GLuint program);
    void draw(glm::vec3 cameraPosition);

private:
    const std::vector<GLfloat>& vertices();

    static const std::vector<GLfloat> mVertices;

    GLuint mVao;
    GLuint mCubeBuffer;
    GLuint mCubeIndexBuffer;
    GLuint mProgram;
    GLuint cubeTexture;
};


#endif //PROJECT_SKYBOX_HPP

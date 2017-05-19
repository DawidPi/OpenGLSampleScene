//
// Created by dapl on 2017-05-19.
//

#ifndef PROJECT_LIGHTMODEL_HPP
#define PROJECT_LIGHTMODEL_HPP


#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <vector>

class SphereModel {
public:
    SphereModel(const glm::vec3& color, double radius, unsigned int rows, unsigned int cols);
    void init();
    void draw(GLuint program, const glm::mat4 &model);

private:
    glm::vec4 mColor;
    std::vector<glm::vec4> mVertices;

    GLuint mVao;
    GLuint mSphereBuffer;
    GLuint mSphereIndexBuffer;
    GLuint mSphereColorBuffer;
    GLuint mSphereNormalsBuffer;

    std::vector<glm::vec4> &vertices();
    std::vector<glm::vec4> mColors;

    std::vector<glm::vec4> &colors();

    std::vector<glm::vec4> &normals();

    std::vector<glm::vec4> mNormals;
};


#endif //PROJECT_LIGHTMODEL_HPP

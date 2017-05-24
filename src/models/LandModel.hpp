//
// Created by dapl on 2017-05-12.
//

#ifndef PROJECT_LANDMODEL_HPP
#define PROJECT_LANDMODEL_HPP


#include <glad/glad.h>
#include <vector>
#include <glm/matrix.hpp>
#include "../Texture.hpp"

class LandModel {
public:

    void init(GLuint i);
    void draw(GLuint program, const glm::mat4 &model);

private:
    const std::vector<GLfloat>& vertices(){
        return vertexBuffer;
    }

    const std::vector<GLfloat>& colors(){
        return colorBuffer;
    }

    const std::vector<GLuint>& indices(){
        return indicesBuffer;
    }

    const std::vector<GLfloat>& normals(){
        return normalsBuffer;
    }

private:
    GLuint mVao;
    GLuint mLandBuffer;
    GLuint mLandIndices;
    GLuint mLandColors;
    GLuint mLandNormals;

    static const std::vector<GLfloat> vertexBuffer;
    static const std::vector<GLfloat> colorBuffer;
    static const std::vector<GLuint> indicesBuffer;
    static const std::vector<GLfloat> normalsBuffer;
    Texture mTextureReader;
};


#endif //PROJECT_LANDMODEL_HPP

//
// Created by dapl on 2017-05-12.
//

#ifndef PROJECT_CUBEMODEL_HPP
#define PROJECT_CUBEMODEL_HPP


#include <glad/glad.h>
#include <vector>

class CubeModel {
public:
    CubeModel();

    void init();
    void draw(GLuint program, const glm::mat4 &model);
private:
    const std::vector<GLfloat>& vertices(){
        return vertexBufferPrim;
    }

    const std::vector<GLfloat>& colors(){
        return colorBuffer;
    }

//    const std::vector<GLuint>& indices(){
//        return indicesBuffer;
//    }

    const std::vector<GLfloat>& normals(){
        return normalsBuffer;
    }

private:
    GLuint mVao;
    GLuint mCubeBuffer;
    GLuint mCubeIndexBuffer;
    GLuint mCubeColorBuffer;
    GLuint mCubeNormalsBuffer;

    static const std::vector<GLfloat> vertexBufferPrim;
    static const std::vector<GLfloat> colorBuffer;
    static const std::vector<GLfloat> normalsBuffer;
//    static const std::vector<GLuint > indicesBuffer;
};


#endif //PROJECT_CUBEMODEL_HPP

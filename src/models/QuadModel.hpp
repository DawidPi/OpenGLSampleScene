//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_QUADMODEL_HPP
#define PROJECT_QUADMODEL_HPP


#include <glad/glad.h>
#include <glm/detail/type_mat.hpp>

class QuadModel {
public:
    void init();
    void draw(GLuint program);

    GLuint mBuffer;
    GLuint mVao;
    std::size_t mBufferIndices;
    GLuint mTexCoordBuffer;
};


#endif //PROJECT_QUADMODEL_HPP

//
// Created by dapl on 2017-06-02.
//

#ifndef PROJECT_FRAMEBUFFER_HPP
#define PROJECT_FRAMEBUFFER_HPP


#include <glad/glad.h>

class Framebuffer {
public:
    void init(unsigned int width, unsigned int height, GLuint textureID);
    void attachFramebuffer();
    void detachFramebuffer();
    void attachTexture(GLint uniformLocation);
    void castToScreen();

private:

    unsigned int mHeight;
    unsigned int mWidth;
    GLuint mFramebuffer;
    GLuint mTexture;
    GLuint mDepthBuffer;
    GLuint mTextureId;
};


#endif //PROJECT_FRAMEBUFFER_HPP

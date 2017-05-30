//
// Created by dapl on 2017-05-30.
//

#ifndef PROJECT_CASUALFRAMEBUFFER_HPP
#define PROJECT_CASUALFRAMEBUFFER_HPP


class CasualFramebuffer {
public:
    void init(unsigned int width, unsigned int height);
    void attachFramebuffer();
    void detachFramebuffer();
    void attachTexture(GLint uniformLocation);

private:
    unsigned int mWidth;
    unsigned int mHeight;
    GLuint mFramebuffer;
    GLuint mTexture;
    GLuint mDepthBuffer;
};


#endif //PROJECT_CASUALFRAMEBUFFER_HPP

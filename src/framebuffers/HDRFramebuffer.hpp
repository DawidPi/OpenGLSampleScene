//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_HDRFRAMEBUFFER_HPP
#define PROJECT_HDRFRAMEBUFFER_HPP

#include <glad/glad.h>

class HDRFramebuffer {
public:
    void init(unsigned int width, unsigned int height);
    void attachFramebuffer() const ;
    void detachFramebuffer() const ;
    void attachTexture() const ;

    ~HDRFramebuffer();
private:
    GLuint mTextureId;
    GLuint mFramebuffer;
    GLuint mDepthBuffer;
    unsigned int mWidth;
    unsigned int mHeight;
};


#endif //PROJECT_HDRFRAMEBUFFER_HPP

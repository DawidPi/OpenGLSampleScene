//
// Created by dapl on 2017-05-23.
//

#ifndef PROJECT_HDRFRAMEBUFFER_HPP
#define PROJECT_HDRFRAMEBUFFER_HPP

#include <glad/glad.h>

class MSAAFramebuffer {
public:
    void init(unsigned int width, unsigned int height);
    void attachFramebuffer() const ;
    void detachFramebuffer() const ;
    void attachTexture(GLint uniformLocation) const ;
    void calculate2DTexture() const;
    GLuint noMSAAID(){
        return mNoMSAAFramebuffer;
    }

    ~MSAAFramebuffer();
private:
    GLuint mMSAATexture;
    GLuint mNoMSAATexture;
    GLuint mMSAAFramebuffer;
    GLuint mNoMSAAFramebuffer;
    GLuint mDepthBuffer;
    GLuint mDepthFlatBuffer;

    unsigned int mWidth;

    unsigned int mHeight;

    void setUpNoMsaaFramebuffer(unsigned int width, unsigned int height);
};


#endif //PROJECT_HDRFRAMEBUFFER_HPP

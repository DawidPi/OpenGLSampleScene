//
// Created by dapl on 2017-05-30.
//

#ifndef PROJECT_DOWNSAMPLINGFRAMEBUFFER_HPP
#define PROJECT_DOWNSAMPLINGFRAMEBUFFER_HPP

#include <glad/glad.h>

class DownSamplingFramebuffer {
public:
    void init(unsigned int width, unsigned int height);
    void downSampleFromFramebuffer(GLuint otherFramebufferId, unsigned int otherWidth,
                                   unsigned int otherHeight);
    void attachTexture(GLint uniformLocation);

    void attachFramebuffer();
    void detachFramebuffer();

    ~DownSamplingFramebuffer();
private:

    unsigned int mWidth;
    unsigned int mHeight;
    GLuint mFramebuffer;
    GLuint mDownsampledTexture;
};


#endif //PROJECT_DOWNSAMPLINGFRAMEBUFFER_HPP

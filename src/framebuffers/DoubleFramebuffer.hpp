//
// Created by dapl on 2017-05-30.
//

#ifndef PROJECT_CASUALFRAMEBUFFER_HPP
#define PROJECT_CASUALFRAMEBUFFER_HPP


class DoubleFramebuffer {


    enum Usage {FIRST, SECOND, NONE};

public:
    void init(unsigned int width, unsigned int height);
    void attachFramebuffer();
    void detachFramebuffer();
    void attachTexture(GLint uniformLocation);
    void swap();
    void castToScreen();

    void swapFramebuffer();

    void swapTexture(GLint newUniformLocation);

private:
    unsigned int mWidth;
    unsigned int mHeight;
    GLuint mFirstFramebuffer;
    GLuint mFirstTexture;
    GLuint mFirstDepthBuffer;
    GLuint mSecondFramebuffer;
    GLuint mSecondTexture;
    GLuint mSecondDepthBuffer;
    Usage mCurrentlyUsed;
    GLint mLastUniformLocation;
    bool mTextureAttached=false;
    Usage mCurrentlyBoundTexture = NONE;
};


#endif //PROJECT_CASUALFRAMEBUFFER_HPP

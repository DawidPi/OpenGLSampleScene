//
// Created by dapl on 2017-05-22.
//

#ifndef PROJECT_TEXTURE_HPP
#define PROJECT_TEXTURE_HPP

#include <string>
#include <stb_image.h>
#include <glad/glad.h>

class Texture {
public:
    unsigned int load(std::string path, GLuint i);
    void attach();
    void detach();

    ~Texture();
private:
    GLuint mTextureId;
    GLuint mGlProgram;
    stbi_uc *mData;
};


#endif //PROJECT_TEXTURE_HPP

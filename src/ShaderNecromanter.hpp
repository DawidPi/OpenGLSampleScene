//
// Created by dapl on 2017-05-11.
//

#ifndef PROJECT_SHADERNECROMANTER_HPP
#define PROJECT_SHADERNECROMANTER_HPP


#include <glad/glad.h>

class ShaderNecromanter {
public:
    GLuint spawnShader(GLuint shaderType, const char* shaderPath);
};


#endif //PROJECT_SHADERNECROMANTER_HPP

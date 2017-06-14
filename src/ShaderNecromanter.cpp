//
// Created by dapl on 2017-05-11.
//

#include <vector>
#include <stdexcept>
#include <fstream>
#include "ShaderNecromanter.hpp"

GLuint ShaderNecromanter::spawnShader(GLuint shaderType, const char *shaderPath) {
    auto createdShader = glCreateShader(shaderType);
    std::string stream;
    std::ifstream createdShaderFile;
    createdShaderFile.open(shaderPath);
    stream = std::string((std::istreambuf_iterator<char>(createdShaderFile)), std::istreambuf_iterator<char>());
    const char* rawSource = stream.c_str();
    glShaderSource(createdShader, 1, &rawSource, nullptr);
    glCompileShader(createdShader);

    GLint success;
    glGetShaderiv(createdShader, GL_COMPILE_STATUS, &success);
    if(success == GL_FALSE){
        GLint log_size=0;
        glGetShaderiv(createdShader, GL_INFO_LOG_LENGTH, &log_size);
        std::vector<GLchar> errorLog((unsigned long) log_size);
        glGetShaderInfoLog(createdShader, (GLsizei) errorLog.size(), nullptr, errorLog.data());

        glDeleteShader(createdShader);
        createdShaderFile.close();
        throw std::runtime_error(&errorLog[0]);
    }


    createdShaderFile.close();
    return createdShader;
}

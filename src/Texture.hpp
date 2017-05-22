//
// Created by dapl on 2017-05-22.
//

#ifndef PROJECT_TEXTURE_HPP
#define PROJECT_TEXTURE_HPP

#include <string>
#include <stb_image.h>

class Texture {
public:
    unsigned int load(const std::string& path);
};


#endif //PROJECT_TEXTURE_HPP

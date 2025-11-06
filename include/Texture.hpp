#pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <string>
#include "PPMParser.hpp"

class Texture
{
private:

public:
    Texture(const std::string &filePath);
    ~Texture() = default;
};


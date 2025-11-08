#pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <string>
#include "PPMParser.hpp"

class Texture
{
private:
    unsigned int texture = 0;
    int width = 0;
    int height = 0;

public:
    Texture(const std::string &filePath);
    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;
    ~Texture();

    void bind(unsigned int unit = 0) const;
    int getWidth() const;
    int getHeight() const;
    GLuint getID() const;

    static void unbind();
};


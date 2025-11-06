#include "Texture.hpp"

Texture::Texture(const std::string &filePath)
{
    PPMParser textureObject(filePath);
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textureObject.getData())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureObject.getWidth(), textureObject.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, textureObject.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        throw std::runtime_error("Failed to load texture\n");
}

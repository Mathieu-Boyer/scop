#include "Texture.hpp"


void Texture::unbind(){
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::Texture(const std::string &filePath) 
{
    PPMParser textureObject(filePath);

    width  = textureObject.getWidth();
    height = textureObject.getHeight();

    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (textureObject.getData())
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, textureObject.getData());
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
        throw std::runtime_error("Failed to load texture\n");
}


void Texture::bind(unsigned int unit) const{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, texture);
}

int Texture::getWidth() const{
    return width;
}
int Texture::getHeight() const{
    return height;
}
GLuint Texture::getID() const{
    return texture;
}

Texture::~Texture(){
    if (texture) glDeleteTextures(1, &texture);
}
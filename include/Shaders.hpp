#pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include <string>
#include <fstream>
#include <iostream>

class Shaders
{
private:
    void checkShaderCompile (GLuint shader, const std::string &name);
    void shaderCompile (GLenum type, GLuint &shader,  const std::string &name, std::string &shaderFileContent);
    const std::string loadShader(const std::string &shaderName);
    
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint shaderProgram;

    std::string vertexShaderFileContent;
    std::string fragmentShaderFileContent;


public:
    Shaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath);
    ~Shaders();

    Shaders(const Shaders&) = delete;
    Shaders& operator=(const Shaders&) = delete;

    Shaders(Shaders&&) = default;
    Shaders& operator=(Shaders&&) = default;
    void use();
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};


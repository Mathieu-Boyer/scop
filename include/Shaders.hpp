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
    
    void use();
};


# pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <memory>
#include "Shaders.hpp"
#include "Texture.hpp"
#include "OBJParser.hpp"



class GLApp
{
private:
    OBJParser test;

    GLFWwindow *window = NULL;
    std::unique_ptr<Shaders> shader;
    float currentProgress = 0;
    void transitionIncrementation(float factor);
public:
    GLApp(unsigned int width, unsigned int height, const char *windowName, const std::string &objPath = "models/42.obj");
    ~GLApp();

    // void setShaders(std::unique_ptr<Shaders> shaders);
    bool textureIsOff = true;
    bool textureColorAreInverted = false;
    bool transitionIsEnabled = false;
    bool wavesAreEnabled = false;

    void render();
    void textureTransition();
    void invertTextureColors();
    void waves();

    int speed;

    // void invertTextureColors();

    // Shaders &getShader() { return *shader; }
    // const Shaders &getShader() const { return *shader; }
};
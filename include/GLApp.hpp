# pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <memory>
#include "Shaders.hpp"
#include "Texture.hpp"


class GLApp
{
private:
    GLFWwindow *window = NULL;
    std::unique_ptr<Shaders> shader;
    float currentProgress = 0;
    void transitionIncrementation(float factor);
public:
    GLApp(unsigned int width, unsigned int height, const char *windowName);
    ~GLApp();

    // void setShaders(std::unique_ptr<Shaders> shaders);
    bool textureIsOff = true;

    bool transitionIsEnabled = false;

    void render();
    void textureTransition();

    // Shaders &getShader() { return *shader; }
    // const Shaders &getShader() const { return *shader; }
};
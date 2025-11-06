# pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <memory>
#include "Shaders.hpp"
#include "PPMParser.hpp"


class GLApp
{
private:
    GLFWwindow *window = NULL;
    std::unique_ptr<Shaders> _shaders = nullptr;
    

public:
    GLApp(unsigned int width, unsigned int height, const char *windowName);
    ~GLApp();

    void setShaders(std::unique_ptr<Shaders> shaders);
    void render();
    Shaders &shaders() { return *_shaders; }
    const Shaders &shaders() const { return *_shaders; }
};
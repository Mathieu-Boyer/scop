# pragma once
#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl3.h>
#include "GLFW/glfw3.h"
#include <memory>
#include "Shaders.hpp"
#include "Texture.hpp"
#include "OBJParser.hpp"
#include "Scene.hpp"



class GLApp
{
private:

    GLFWwindow *window = NULL;
    const std::string &objPath;
    const std::string &objTexture;
public:
    GLApp(unsigned int width, unsigned int height, const char *windowName, const std::string &objPath = "models/42.obj", const std::string &objTexture = "textures/wood.ppm");
    ~GLApp();

    // void setShaders(std::unique_ptr<Shaders> shaders);
    void render();

    int speed;
};
#pragma once 

#include "OBJParser.hpp"
#include "Shaders.hpp"
#include "Texture.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Renderable.hpp"
#include <string>
#include <array>

class Scene
{
private:

    OBJParser object;
    OBJParser lightingObject;
    Shaders shader;
    Shaders lightingShader;
    Texture texture;
    Mesh mesh;
    Mesh cube;
    Camera camera;
    Renderable lightCube;
    Renderable meshInstance;

    LinearAlgebra::mat4 view;
    LinearAlgebra::mat4 projection;
    int speed;
    float currentProgress = 0;

public:

    void transitionIncrementation(float factor);

    std::array<int, 2> keyFlags;

    void updateLightPosition(int currentFlag);

    bool textureIsOff = true;
    bool textureColorAreInverted = false;
    bool transitionIsEnabled = false;
    bool wavesAreEnabled = false;
    void textureTransition();
    void invertTextureColors();
    void waves();

    Renderable &getLightCube() { return lightCube;};
    const Renderable &getLightCube() const { return lightCube;};
    Scene(const std::string &objectPath, const std::string &texturePath);
    void render();
    ~Scene();
};


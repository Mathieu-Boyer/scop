#include "Scene.hpp"

Scene::Scene(const std::string &objectPath, const std::string &texturePath) :
    object(objectPath) , lightingObject("models/cube.obj"),
    shader("shaders/default.vs", "shaders/default.fs"), lightingShader("shaders/lighting.vs", "shaders/lighting.fs"),
    texture(texturePath),
    mesh(object.getVertices(), object.getObjData()), cube(lightingObject.getVertices(), lightingObject.getObjData()),
    camera((LinearAlgebra::vec3){0.0f, 0.0f, 10.f}),
    lightCube(cube, NULL), meshInstance(mesh, &texture),
    lightSelected(false)
{
    view = camera.getViewMatrix();
    projection = camera.getProjectionMatrix();
    meshInstance.getTransform().scale = object.scalingVector();
    lightCube.getTransform().scale = {.1,.1,.1};
    lightCube.getTransform().translation = {-1, 1, 2};
    speed = 50;
}

Scene::~Scene()
{
}


void Scene::waves(){
    shader.use();
    wavesAreEnabled = !wavesAreEnabled;
    shader.setBool("wavesAreEnabled", wavesAreEnabled);
    std::cout << wavesAreEnabled << "\n";
}

void Scene::invertTextureColors(){
    shader.use();
    textureColorAreInverted = !textureColorAreInverted;
    shader.setBool("textureColorAreInverted", textureColorAreInverted);
}


void Scene::transitionIncrementation(float factor){
    shader.use();
    currentProgress += factor;
    shader.setFloat("progress", currentProgress);
    if (currentProgress >= 1)
        transitionIsEnabled = false;
}
void Scene::textureTransition(){
    if (!textureIsOff && currentProgress < 1)
        transitionIncrementation(0.02);
    else if (textureIsOff && currentProgress > 0)
        transitionIncrementation(-0.02);
}

void Scene::updateObjectPosition(int currentFlag){

    LinearAlgebra::vec3 &object = lightSelected ? lightCube.getTransform().translation : meshInstance.getTransform().translation;
    if (currentFlag == GLFW_KEY_LEFT)
        object.x -= .05;
    if (currentFlag == GLFW_KEY_RIGHT)
        object.x += .05;

    if (currentFlag == GLFW_KEY_UP)
        object.y += .05;
    if (currentFlag == GLFW_KEY_DOWN)
        object.y -= .05;
    
    if (currentFlag == GLFW_KEY_LEFT_SHIFT)
        object.z += .05;
    if (currentFlag == GLFW_KEY_LEFT_CONTROL)
        object.z -= .05;
}


void Scene::render() {

        if (transitionIsEnabled)
            textureTransition();

        for (auto &arrowFlag : keyFlags)
            updateObjectPosition(arrowFlag);

        float time = glfwGetTime();
        shader.use();
        shader.setFloat("time", time);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        meshInstance.getTransform().rotation = {0, time * speed, 0};

        shader.setVec3("lightPosition", lightCube.getTransform().translation);

        lightingShader.use();
        lightingShader.setMat4("view", view);
        lightingShader.setMat4("projection", projection);


        meshInstance.draw(shader);
        lightCube.draw(lightingShader);
}

#include "GLApp.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "transform.hpp"
#include "Renderable.hpp"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    (void)scancode;
    (void)mods;
    GLApp *app = static_cast<GLApp *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_T && action == GLFW_PRESS){
        app->transitionIsEnabled = true;
        app->textureIsOff = !app->textureIsOff;
    }

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
        app->invertTextureColors();

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        app->waves();
}

void GLApp::waves(){
    wavesAreEnabled = !wavesAreEnabled;
    shader->setBool("wavesAreEnabled", wavesAreEnabled);
}

GLApp::GLApp(unsigned int width, unsigned int height, const char *windowName, const std::string &objPath) : test(objPath){

        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, windowName, NULL, NULL);

        if (!window){
            std::cerr << "Window couldn't be openned\n";
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_BLEND );
        glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
        glfwSetWindowUserPointer(window, this);
        glfwSetKeyCallback(window, keyCallback);
}

void GLApp::invertTextureColors(){
    shader->use();
    textureColorAreInverted = !textureColorAreInverted;
    shader->setBool("textureColorAreInverted", textureColorAreInverted);
}


void GLApp::transitionIncrementation(float factor){
    shader->use();
    currentProgress += factor;
    shader->setFloat("progress", currentProgress);
    if (currentProgress >= 1)
        transitionIsEnabled = false;
}
void GLApp::textureTransition(){
    if (!textureIsOff && currentProgress < 1)
        transitionIncrementation(0.02);
    else if (textureIsOff && currentProgress > 0)
        transitionIncrementation(-0.02);
}

void GLApp::render(){

    shader = std::make_unique<Shaders>("shaders/default.vs", "shaders/default.fs");

    Texture brickTexture("textures/mario.ppm");
    Mesh cube(test.getVertices(), test.getObjData());

    Camera camera(LinearAlgebra::vec3(0.0f, 0.0f, 6.f));
    LinearAlgebra::mat4 view = camera.getViewMatrix();
    LinearAlgebra::mat4 projection = camera.getProjectionMatrix();
    Renderable cubeInstance(cube, brickTexture);
    cubeInstance.getTransform().scale = test.scalingVector();
    speed = 150;

    float r = 79;
    float g = 85;
    float b = 109;
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();

        if (transitionIsEnabled)
            this->textureTransition();
        if (wavesAreEnabled)
            shader->setFloat("time",glfwGetTime());


        glClearColor(r/255, g/255, b/255, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float time = glfwGetTime();

        cubeInstance.getTransform().rotation = {0,time * speed, 0};
        shader->use();


        // shader->setFloat("time", glfwGetTime());
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        cubeInstance.draw(*shader);
        // cubeInstance2.draw(*shader);
        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

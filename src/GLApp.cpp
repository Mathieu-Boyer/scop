#include "GLApp.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "transform.hpp"
#include "Renderable.hpp"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    (void)scancode;
    (void)mods;
    GLApp *app = static_cast<GLApp *>(glfwGetWindowUserPointer(window));
    // (void)app;

    if (key == GLFW_KEY_T && action == GLFW_PRESS){
        app->transitionIsEnabled = true;
        app->textureIsOff = !app->textureIsOff;
    }
}

GLApp::GLApp(unsigned int width, unsigned int height, const char *windowName){

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

    // OBJParser test("models/withTexture.obj");
    OBJParser test("models/42.obj");
    shader = std::make_unique<Shaders>("shaders/default.vs", "shaders/default.fs");
    // Texture brickTexture("textures/brickwall1.ppm");
    Texture brickTexture("textures/wood.ppm");
    Mesh cube(test.getVertices(), test.getObjData());

    Camera camera(LinearAlgebra::vec3(0.0f, 0.0f, 4.f));
    LinearAlgebra::mat4 view = camera.getViewMatrix();
    LinearAlgebra::mat4 projection = camera.getProjectionMatrix();
    Renderable cubeInstance(cube, brickTexture);

    // cubeInstance.getTransform().scale = {.1,.1,.1};
    int speed = 50;

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        if (transitionIsEnabled)
            this->textureTransition();
        glClearColor(.1, .2, .4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float time = glfwGetTime();
        // cubeInstance.getTransform().translation = {0,(sin(time /2)), 0};
        // cubeInstance.getTransform().scale = {(sin(time) / 2) + 1.f, (sin(time) / 2) + 1.f, (sin(time) / 2) + 1.f};
        cubeInstance.getTransform().rotation = {0,time * speed, 0};
        shader->use();
        shader->setMat4("view", view);
        shader->setMat4("projection", projection);
        cubeInstance.draw(*shader);
        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

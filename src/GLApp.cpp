#include "GLApp.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "transform.hpp"
#include "Renderable.hpp"

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
}

void GLApp::render(){

    // OBJParser test("models/withTexture.obj");
    OBJParser test("models/mario.obj");
    Shaders shader("shaders/default.vs", "shaders/default.fs");
    // Texture brickTexture("textures/brickwall1.ppm");
    Texture brickTexture("textures/mario.ppm");
    Mesh cube(test.getVertices(), test.getObjData());

    Camera camera(glm::vec3(0.0f, 0.0f, 50.f));
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    Renderable cubeInstance(cube, brickTexture);

    cubeInstance.getTransform().scale = {.2,.2,.2};
    int speed = 50;

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(.1, .2, .4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float time = glfwGetTime();
        // cubeInstance.getTransform().translation = {0,(sin(time /2)), 0};
        // cubeInstance.getTransform().scale = {(sin(time) / 2) + 1.f, (sin(time) / 2) + 1.f, (sin(time) / 2) + 1.f};
        cubeInstance.getTransform().rotation = {0,time * speed, 0};
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        cubeInstance.draw(shader);
        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

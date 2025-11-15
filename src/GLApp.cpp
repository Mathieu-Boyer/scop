#include "GLApp.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "transform.hpp"
#include "Renderable.hpp"

void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods){
    (void)scancode;
    (void)mods;
    Scene *scene = static_cast<Scene *>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_T && action == GLFW_PRESS){
        scene->transitionIsEnabled = true;
        scene->textureIsOff = !scene->textureIsOff;
    }

    if (key == GLFW_KEY_I && action == GLFW_PRESS)
        scene->invertTextureColors();

    if (key == GLFW_KEY_W && action == GLFW_PRESS)
        scene->waves();

    if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) && (action == GLFW_PRESS || action == GLFW_REPEAT))
        scene->keyFlags[0] = key;
    if ((key == GLFW_KEY_LEFT || key == GLFW_KEY_RIGHT) && action == GLFW_RELEASE)
        scene->keyFlags[0] = 0;

    if ((key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && (action == GLFW_PRESS || action == GLFW_REPEAT))
        scene->keyFlags[1] = key;
    if ((key == GLFW_KEY_UP || key == GLFW_KEY_DOWN) && action == GLFW_RELEASE)
        scene->keyFlags[1] = 0;

    // if (key == GLFW_KEY_RIGHT && (action == GLFW_REPEAT || action == GLFW_PRESS))
    //     // lightPosition.x += .1;
    //     ;

}



GLApp::GLApp(unsigned int width, unsigned int height, const char *windowName, const std::string &objPath, const std::string &objTexture) : objPath(objPath), objTexture(objTexture)  {

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

    Scene scene(objPath, objTexture);

    glfwSetWindowUserPointer(window, &scene);
    glfwSetKeyCallback(window, keyCallback);
    float r = 30;
    float g = 30;
    float b = 35;
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        glClearColor(r/255, g/255, b/255, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        scene.render();
        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}

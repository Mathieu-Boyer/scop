#include "GLApp.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
// static float vertices[] = {
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//      0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//      0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//     -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//     -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
// };

std::vector<vertex> vertices = {
    // Back face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

    // Front face
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},
    {{ 0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, 0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f, 0.5f}, {1.0f, 1.0f}},
    {{-0.5f,  0.5f, 0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}},

    // Left face
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},

    // Right face
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},

    // Bottom face
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},

    // Top face
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
    {{ 0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{ 0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
    {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
    {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}}
};

GLApp::GLApp(unsigned int width, unsigned int height, const char *windowName){
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Required on macOS!

        window = glfwCreateWindow(width, height, windowName, NULL, NULL);
        if (!window){
            std::cerr << "Window couldn't be openned\n";
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);

        glEnable(GL_DEPTH_TEST);
}

void GLApp::setShaders(std::unique_ptr<Shaders> shaders){
    _shaders = std::move(shaders);
}



void GLApp::render(){

    Mesh cube(vertices);
    Texture brickTexture("textures/brickwall1.ppm");

    Camera camera(glm::vec3(0.0f, 0.0f, 3.f));
    glm::mat4 view = camera.getViewMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        glClearColor(.1, .2, .4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float time = glfwGetTime();
        _shaders->use();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::rotate(model, time, glm::vec3(.75f, .5f, .25f));
        _shaders->setMat4("model", model);
        _shaders->setMat4("view", view);
        _shaders->setMat4("projection", projection);

        cube.draw();

        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{

    glfwDestroyWindow(window);
    glfwTerminate();
}

#include "GLApp.hpp"
const GLfloat verticies[] = {
    -0.5f, -0.5f, 0.0f,          0,0,0,
    0.5f, -0.5f, 0.0f,           0,0,0,
    0.0f, 0.5f , 0.0f,           0,0,0
};
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
}

void GLApp::setShaders(std::unique_ptr<Shaders> shaders){
    _shaders = std::move(shaders);
}

void GLApp::render(){
    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(.1, .2, .4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);


        float time = glfwGetTime();

        _shaders->setFloat("R", (sin(time * 0.5)/2) + 0.5);
        _shaders->setFloat("G", (sin(time)/2) + 0.5);
        _shaders->setFloat("B", (sin(time * 2)/2) + 0.5);

        _shaders->use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,3);

        glfwSwapBuffers(window);
    }
}

GLApp::~GLApp()
{

    glfwDestroyWindow(window);
    glfwTerminate();
}

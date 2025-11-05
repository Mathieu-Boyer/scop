#include "main.hpp"

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){"
"gl_Position = vec4(aPos, 1.0);"
"}\0";

const char *fragmentShaderSource = 
"#version 330 core\n"
"out vec4 fragColor;\n"
"void main(){"
"fragColor = vec4(.4, .2, .8, 1.0);"
"}\0";

int main (){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    GLFWwindow *window = glfwCreateWindow(800, 800, "Scop", NULL, NULL);

    if (!window){
        std::cerr << "Window couldn't be openned\n";
        glfwTerminate();
    }

    glfwMakeContextCurrent(window);




    glfwDestroyWindow(window);
    glfwTerminate();
}
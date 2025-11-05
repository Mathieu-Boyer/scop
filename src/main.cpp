#include "main.hpp"




const GLfloat verticies[] = {

    // pos --------------------- color
    -0.5f, -0.5f, 0.0f,          1,0,0,
    0.5f, -0.5f, 0.0f,           0,1,0,
    0.0f, 0.5f , 0.0f,           0,0,1
};

int main (){
    try {
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
        Shaders shaders("shaders/vertex.glsl", "shaders/fragment.glsl");


    GLuint VBO, VAO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6 ,(void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6 , (void *)(sizeof(float) * 3));
    glEnableVertexAttribArray(1);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClearColor(.1, .2, .4, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shaders.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0,3);

        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    } catch (std::exception &err){
        std::cerr << err.what() << "\n";
    }
}
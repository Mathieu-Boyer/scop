#include "Shaders.hpp"

Shaders::Shaders(const std::string &vertexShaderPath, const std::string &fragmentShaderPath){
    vertexShaderFileContent = loadShader(vertexShaderPath);
    fragmentShaderFileContent = loadShader(fragmentShaderPath);

    shaderCompile(GL_VERTEX_SHADER, vertexShader, "vertexShader", vertexShaderFileContent);
    shaderCompile(GL_FRAGMENT_SHADER, fragmentShader, "fragmentShader", fragmentShaderFileContent);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shaders::shaderCompile(GLenum type, GLuint &shader,  const std::string &name, std::string &shaderFileContent) {
    const char *shaderSource = shaderFileContent.c_str();
    shader = glCreateShader(type);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    checkShaderCompile(shader, name);
}

void Shaders::checkShaderCompile (GLuint shader, const std::string &name){
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
        throw std::runtime_error("ERROR: Shader compilation failed (" + name + ")\n" + infoLog + "\n");
    } else
        std::cout << "Shader compiled successfully: " << name << std::endl;
};

const std::string Shaders::loadShader(const std::string &shaderName){

    std::ifstream file(shaderName);
    std::string content;

    if (!file.is_open())
        throw std::runtime_error("Failed to open file: " + shaderName + "\n");

    std::string line;
    while (std::getline(file, line))
        content += line + '\n';
    
    file.close();
    return content;
}

void Shaders::use(){
    glUseProgram(shaderProgram);
}

void Shaders::setBool(const std::string &name, bool value) const {         
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), (int)value); 
}
void Shaders::setInt(const std::string &name, int value) const { 
    glUniform1i(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}
void Shaders::setFloat(const std::string &name, float value) const { 
    glUniform1f(glGetUniformLocation(shaderProgram, name.c_str()), value); 
}

void Shaders::setVec3(const std::string &name, LinearAlgebra::vec3 vec) const{
    unsigned int loc = glGetUniformLocation(shaderProgram, name.c_str());
    glUniform3fv(loc, 1, (GLfloat *)&vec);
}


void Shaders::setMat4(const std::string &name, LinearAlgebra::mat4 mat){
    unsigned int loc = glGetUniformLocation(shaderProgram, name.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, &mat.data[0]);
}

Shaders::~Shaders()
{
    glDeleteProgram(shaderProgram);
}

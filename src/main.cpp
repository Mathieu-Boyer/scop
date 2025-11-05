#include "main.hpp"

const char *vertexShaderSource = 
"#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){"
"gl_Position = vec4(aPos, 1.0);"
"}\0";

int main (){


}
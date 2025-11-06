#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 myColor;
uniform float R;
uniform float G;
uniform float B;

void main(){
    gl_Position = vec4(aPos, 1.0);
    myColor = vec3(aColor.x + R, aColor.y + G, aColor.z + B);
}
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;
out vec2 myTextCoor;
out vec3 myColor;
uniform float R;
uniform float G;
uniform float B;

void main(){
    gl_Position = vec4(aPos, 1.0);
    myTextCoor = myTextCoor = vec2(aText.x, 1.0 - aText.y);
    myColor = vec3(R, G, B);
}
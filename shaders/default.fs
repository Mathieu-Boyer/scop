#version 330 core
in vec2 myTextCoor;
out vec4 fragColor;

uniform sampler2D myTexture;

void main(){
    fragColor = texture(myTexture, myTextCoor);
}
#version 330 core
in vec2 myTextCoor;
in vec3 myColor;
out vec4 fragColor;

uniform sampler2D myTexture;

void main(){
    fragColor = texture(myTexture, myTextCoor) * vec4(myColor, 1.0);
}
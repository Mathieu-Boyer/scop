#version 330 core
in vec2 myTextCoor;
in vec4 myColor;
out vec4 fragColor;

uniform sampler2D myTexture;
uniform float progress;

void main(){
    vec4 tex = texture(myTexture, myTextCoor);

    fragColor = mix(myColor, tex , progress);

    // fragColor *= tex;
}
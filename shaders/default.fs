#version 330 core
in vec2 myTextCoor;
in vec4 myColor;
out vec4 fragColor;

uniform sampler2D myTexture;
uniform float progress;
uniform bool textureColorAreInverted;

void main(){
    vec4 tex = texture(myTexture, myTextCoor);
    if (textureColorAreInverted)
        tex = vec4(tex.b,tex.g, tex.r, tex.a);

    fragColor = mix(myColor, tex , progress);
}
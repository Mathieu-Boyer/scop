#version 330 core
in vec2 myTextCoor;
in vec4 myColor;
in vec3 myNormal;
in vec3 currentPosition;
out vec4 fragColor;


uniform vec3 lightPosition;

uniform sampler2D myTexture;
uniform float progress;
uniform bool textureColorAreInverted;

void main(){

    // texture
    vec4 tex = texture(myTexture, myTextCoor);
    if (textureColorAreInverted)
        tex = vec4(tex.b,tex.g, tex.r, tex.a);

    vec4 lightColor = vec4(1,1,1,1);
    vec3 normal = normalize(myNormal);
    vec3 lightDirection = normalize(lightPosition - currentPosition);
    float diffuse = max(dot(normal, lightDirection), .0);


    fragColor = mix(myColor, tex , progress) * lightColor * (diffuse + .3);
}
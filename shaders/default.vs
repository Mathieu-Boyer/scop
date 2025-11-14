#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;
out vec2 myTextCoor;
out vec4 myColor;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform bool wavesAreEnabled;

void main()
{
    vec3 tempPos = aPos;
    if (wavesAreEnabled){
        float test1 = aPos.x * 1.0;
        float test2 = time * 2.0;
        float amp = .5;
        float phase = (test1 + test2);

        tempPos.y += sin(phase) * amp;
    }
    // tempPos.x += sin(phase) * amp;

    gl_Position = projection * view * model * vec4(tempPos, 1.0);
    myTextCoor = vec2(aText.x, 1.0 - aText.y);
    myColor = vec4(aColor, 1.0);
}
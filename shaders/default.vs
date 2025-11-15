#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aText;
layout (location = 3) in vec3 aNormal;

out vec2 myTextCoor;
out vec3 myNormal;
out vec4 myColor;
out vec3 currentPosition;
uniform mat4 transform;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;
uniform bool wavesAreEnabled;

void main()
{
    currentPosition = vec3(model * vec4(aPos, 1));

    if (wavesAreEnabled){
        float test1 = aPos.x * 1.0;
        float test2 = time * 2.0;
        float amp = .5;
        float phase = (test1 + test2);

        currentPosition.y += sin(phase) * amp;
    }
    // tempPos.x += sin(phase) * amp;

    gl_Position = projection * view * vec4(currentPosition, 1.0);
    myTextCoor = vec2(aText.x, 1.0 - aText.y);
    myColor = vec4(aColor, 1.0);

    myNormal = normalize(transpose(inverse(mat3(model))) * aNormal);
}
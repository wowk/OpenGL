#version 430 core

layout(location = 0) in vec3 pos;

uniform vec2 moveOffset = vec2(0.0f, 0.0f);

void main()
{
    vec3 newPos = pos + vec3(moveOffset, 0.0f);
    gl_Position = vec4(newPos, 1.0f);
}

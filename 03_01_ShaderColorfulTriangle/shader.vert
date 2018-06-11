#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 color;

out vec3 vertColor;

void main()
{
    vertColor = color;
    gl_Position = vec4(pos, 1.0f);
}

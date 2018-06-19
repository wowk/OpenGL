#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 coord;

out vec3 vPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    vPos = pos;
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}

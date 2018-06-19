#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 coord;

out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    texCoord = vec2(coord.x, 1.0f - coord.y);
    gl_Position = proj * view * model * vec4(pos, 1.0f);
    //gl_Position = model * vec4(pos, 1.0f);
}

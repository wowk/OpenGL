#version 330 core

layout(location = 0 ) in vec3 pos;
layout(location = 1 ) in vec3 normal;
layout(location = 2 ) in vec2 coord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Pos;
out vec3 Normal;
out vec2 Coord;

void main()
{
    Pos     = pos;
    Normal  = normal;
    Coord   = vec2(coord.x, 1 - coord.y);
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}

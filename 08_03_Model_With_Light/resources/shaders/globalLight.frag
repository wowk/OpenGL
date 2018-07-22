#version 330 core

uniform vec3 Color;

in vec2 Coord;
in vec3 Pos;
out vec4 color;

void main()
{
    color = vec4(Color, 1.0f);
    //color = vec4(1.0f);
}

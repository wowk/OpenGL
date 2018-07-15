#version 330 core

uniform sampler2D textureSampler1;

in vec2 Coord;
in vec3 Pos;
out vec4 color;

void main()
{
    color = texture2D(textureSampler1, Coord);
    //color = vec4(1.0f);
}

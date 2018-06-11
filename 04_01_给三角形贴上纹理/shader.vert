#version 430 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 coord;

uniform vec2 moveOffset = vec2(0.0f, 0.0f);
out vec2 texCoord;
out vec3 vertPos;

void main()
{
    vertPos = pos + vec3(moveOffset, 0.0f);
    texCoord = coord;
    gl_Position = vec4(pos.x + moveOffset.x, - pos.y + moveOffset.y, pos.z, 1.0f);
}

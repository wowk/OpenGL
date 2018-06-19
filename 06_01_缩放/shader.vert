#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 coord;

uniform float scale;
uniform mat4 projection;
uniform mat4 model;
uniform mat4 view;
uniform vec2 moveOffset = vec2(0.0f, 0.0f);
out vec2 texCoord;
out vec3 vertPos;

void main()
{
    vertPos = pos + vec3(moveOffset, scale);
    texCoord = vec2(coord.x, -coord.y);
    gl_Position = projection * view * model * vec4(vertPos, 1.0f);// * projection;
}

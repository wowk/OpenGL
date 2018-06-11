#version 430 core

layout(location = 0) in vec3 pos;

out vec3 vertColor;
uniform vec2 moveOffset = vec2(0.0f, 0.0f);

void main()
{
    vertColor = vec3(pos.xy + moveOffset, pos.z);
    gl_Position = vec4(pos.x + moveOffset.x, pos.y + moveOffset.y, pos.z, 1.0f);
}

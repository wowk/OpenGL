#version 430 core

out vec4 color;

uniform vec3 vertColor = vec3(1.0f, 0.0f, 0.0f);

void main()
{
    color = vec4(vertColor, 1.0f);
}

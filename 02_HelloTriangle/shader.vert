#version 430 core

layout(location = 0) in vec3 pos;

out vec3 vertPos;

void main()
{
    vertPos = pos;
    gl_Position = vec4(pos, 1.0f);
}

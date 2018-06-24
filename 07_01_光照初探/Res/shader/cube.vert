#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    FragPos = vec3(model * vec4(pos, 1.0f));
    //将顶点的法向量传递给 frag shader
    Normal = normal;
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}

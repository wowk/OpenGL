#version 330 core

layout(location = 0 ) in vec3 pos;
layout(location = 1 ) in vec3 normal;
layout(location = 2 ) in vec2 coord;


uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 texCoord;

void main()
{
    fragPos     = pos;
    fragNormal  = normal;
    texCoord   = vec2(coord.x, 1 - coord.y);
    gl_Position = proj * view * model * vec4(pos, 1.0f);
}

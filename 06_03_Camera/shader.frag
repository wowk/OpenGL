#version 430 core

in vec2 texCoord;
out vec4 color;

uniform sampler2D texSampler1;

void main()
{
    color = texture2D(texSampler1, texCoord);
}

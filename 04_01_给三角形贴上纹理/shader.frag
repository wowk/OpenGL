#version 430 core

in vec2 texCoord;
out vec4 color;
in vec3 vertPos;

uniform vec3 vertColor = vec3(1.0f, 0.0f, 0.0f);

uniform sampler2D texSample2D;

void main()
{

    vec3 newColor = mix(texture2D(texSample2D, texCoord).xyz, vertColor, vertPos.x);
    color = vec4(newColor, 1.0f);
}

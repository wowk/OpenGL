#version 330 core

in vec2 texCoord;
out vec4 color;
in vec3 vertPos;

uniform vec3 vertColor = vec3(1.0f, 0.0f, 0.0f);
uniform sampler2D texture1Sampler2D;
uniform sampler2D texture2Sampler2D;

void main()
{

    vec4 tex1 = texture2D(texture1Sampler2D, texCoord);
    vec4 tex2 = texture2D(texture2Sampler2D, texCoord);
    color = mix(tex1, tex2, 0.5f);
}

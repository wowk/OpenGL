#version 330 core

in vec3 vPos;
out vec4 color;
vec3 ambientLighting = vec3(0.1f, 0.1f, 0.1f);

uniform vec3 surfaceColor;
uniform sampler2D texSampler1;

void main()
{
    //color = texture2D(texSampler1, texCoord);
    if( (abs(vPos.x) >= 0.48f && abs(vPos.y) >= 0.48f)
     || (abs(vPos.z) >= 0.48f && abs(vPos.y) >= 0.48f)
     || (abs(vPos.x) >= 0.48f && abs(vPos.z) >= 0.48f))
    {
        color = vec4(1.0f, 0.0f, 0.0f, 1.0f);
    }else{
        color = vec4(surfaceColor, 1.0f);
    }
}

#version 330 core

uniform vec3 lightPos;
uniform float ambientStrength;
uniform vec3 lightColor;
uniform vec3 cubeColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

void main()
{
    //环境光强度乘以物体的颜色得出的就是物体在没有光照的时候的颜色
    vec3 ambient = ambientStrength * cubeColor;

    //标准化法向量
    vec3 norm = normalize(Normal);

    //通过光源的位置和像素的位置计算出光线的方向（和物理上的方向好像相反？？？）
    vec3 lightDir = normalize(lightPos - FragPos);

    //通过 点乘 计算出 像素法线 和 光线方向向量 的 夹角，
    //这个夹角就当作 光照在 物体上的 强度 来用
    //如果夹角大于90度说明照射不到这个像素，则设为 0.0f
    float diff = max(dot(norm, lightDir), 0.0f);

    ////直接乘以 光线的 颜色， 就能得出光被物体吸收掉的 颜色
    vec3 diffUse = diff * lightColor;

    //环境光照 加上 光源光照 等于总的光照
    //总的光照 乘以 物体的颜色 就计算出了 物体在光照下 呈现出的颜色
    vec3 result = ( ambient + diffUse ) * cubeColor;

    FragColor = vec4(result, 1.0f);
}

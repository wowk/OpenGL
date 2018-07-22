#version 330 core

struct DirectionalLight {
    vec3 color;
};

struct SpotLight {
    vec3 color;
    vec3 front;
    vec3 pos;
    float angle;
    float k0;
    float k1;
    float k2;
};

struct PointLight {
    vec3 color;
};

struct AreaLight {
    vec3 color;
};

struct AmbientLight {
    vec3 color;
};

struct VolumeLight {
    vec3 color;
};

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    int specStrength;
};

struct Light {
    vec3 color;
    vec3 pos;
    vec3 dir;
};

uniform vec3 viewPos;
uniform Light light;
uniform Material material;
uniform sampler2D textureSampler1;

in vec2 texCoord;
in vec3 fragPos;
in vec3 fragNormal;
out vec4 color;


//计算环境光照
vec3 computeAmbient(Material material, Light light)
{
    return material.ambient * light.color;
}

//计算漫反射光照
vec3 computeDiffuse(Material material, Light light, vec3 normal)
{
    return max(dot(normal, light.dir), 0.0f) * material.diffuse * light.color;
}

//计算镜面反射光照
vec3 computeSpecular(Material material, Light light, vec3 vNormal, vec3 vReflect, vec3 vView)
{
    //计算高光反射强度
    float spec = pow(max(dot(vReflect, vView), 0.0f), material.specStrength);
    return  spec * material.specular * light.color;
}

//计算点光源光照衰减
float computeAttenuation(float dist, float k0, float k1, float k2)
{
    return 1.0 / ( k0 + k1 * dist + k2 * dist * dist);
}

//点光源平滑边缘计算
float computeSoftEdge(float inner, float outer, float angle)
{
    //inner 是内圆锥的角度余弦值
    //outer 是外圆锥的角度余弦值
    //angle 是射出光线的角度
    //光线强度为 I = （angle - outer）/（inner - outer）
    float intensity = (angle - outer) / (inner - outer);

    //将强度值约束在 [0.0, 1.0]
    return clamp(intensity, 0.0, 1.0);
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 viewDir = normalize(viewPos - fragPos);
    vec3 reflectDir = normalize(reflect(-light.dir, normal));

    vec3 ambient = computeAmbient(material, light);
    vec3 diffuse = computeDiffuse(material, light, normal);
    vec3 specular = computeSpecular(material, light, normal, reflectDir, viewDir);

    vec4 texture = texture2D(textureSampler1, texCoord);

    color = vec4((ambient + diffuse + specular) * texture.xyz, texture.w);
}

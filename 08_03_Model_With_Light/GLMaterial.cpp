#include <GLMaterial.hpp>


void GLMaterial::setAmbient(const glm::vec3 & ambient)
{
    mAmbient = ambient;
}

void GLMaterial::setDiffuse(const glm::vec3 & diffuse)
{
    mDiffuse = diffuse;
}

void GLMaterial::setSpecular(const glm::vec3 & specular)
{
    mSpecular = specular;
}
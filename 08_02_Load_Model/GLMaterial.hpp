#ifndef GL_MATERIAL_H__
#define GL_MATERIAL_H__

#include <glm/glm.hpp>

class GLMaterial {
public:
    void setAmbient(const glm::vec3 & ambient);
    void setDiffuse(const glm::vec3 & diffuse);
    void setSpecular(const glm::vec3 & specular);

    const glm::vec3 & ambient();
    const glm::vec3 & diffuse();
    const glm::vec3 & specular();

private:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
};

#endif
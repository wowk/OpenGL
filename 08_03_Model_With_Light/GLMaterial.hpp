#ifndef GL_MATERIAL_H__
#define GL_MATERIAL_H__

#include <glm/glm.hpp>

class GLMaterial {
public:
    void setAmbient(const glm::vec3 & ambient);
    void setDiffuse(const glm::vec3 & diffuse);
    void setSpecular(const glm::vec3 & specular);

    inline glm::vec3 & ambient() {
        return mAmbient;
    }
    
    inline glm::vec3 & diffuse() {
        return mDiffuse;
    }

    inline glm::vec3 & specular() {
        return mSpecular;
    }

private:
    glm::vec3 mAmbient;
    glm::vec3 mDiffuse;
    glm::vec3 mSpecular;
};

#endif
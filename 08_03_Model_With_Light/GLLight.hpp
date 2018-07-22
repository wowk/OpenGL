#ifndef GL_LIGHT_H__
#define GL_LIGHT_H__

#include <glm/glm.hpp>
#include <GLModel.hpp>
#include <GLMaterial.hpp>


class GLLight {
public:
    GLLight();

    void setColor(const glm::vec3 & color);
    void setAngle(const glm::vec3 & angle);

    inline glm::vec3 & color() {
        return mColor;
    }

    inline glm::vec3 angle() {
        return mAngle;
    }

private:
    glm::vec3 mColor;
    glm::vec3 mAngle;
};

class GLGlobalLight : public GLLight {

};

class GLSpotLight : public GLLight {

};

#endif
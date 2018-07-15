#ifndef GL_LIGHT_H__
#define GL_LIGHT_H__

#include <glm/glm.hpp>
#include <GLObject.hpp>
#include <GLMaterial.hpp>


class GLLight : public GLObject {
public:
    GLLight();
    GLMaterial & material();
private:
    glm::vec3 color;
    glm::vec3 angle;
    GLMaterial mMaterial;
};

#endif
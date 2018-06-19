#ifndef GL_OBJECT_H__
#define GL_OBJECT_H__

#include <glm/vec3.hpp>
#include <SDL2/SDL.h>

using glm::vec3;


class GLObject {
public:
    explicit GLObject(GLObject* parent = nullptr);
    virtual bool init() = 0;
    virtual ~GLObject();

    virtual void draw(){}

    vec3 position() const;
    void setPosition(const vec3 &position);
    void setZOrder(int zOrder);
private:
    GLObject* m_parent;
    vec3 m_position;
    int m_zOrder;
};

#endif//GL_OBJECT_H__

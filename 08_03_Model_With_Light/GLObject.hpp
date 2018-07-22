#ifndef GL_OBJECT_H__
#define GL_OBJECT_H__

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL2/SDL.h>


class GLObject {
public:
    explicit GLObject(GLObject* parent = nullptr);
    virtual bool init() = 0;
    virtual ~GLObject();

    virtual void draw(){}

    void move(const glm::vec3 & offset);
    void setPosition(const glm::vec3 &position);
    void setZOrder(int zOrder);
    void setScale(const glm::vec3 & scale) {
        mModel = glm::scale(mModel, scale);
    }

    void setRotate(float angle, const glm::vec3 &axis) {
        mModel = glm::rotate(mModel, glm::radians(angle), axis);
    }

    inline glm::vec3 & position() {
        return mPosition;
    }

    inline glm::mat4 & model() {
        return mModel;
    }

private:
    GLObject* mParent;
    glm::vec3 mPosition;
    glm::mat4 mModel;
    int mZOrder;
};

#endif//GL_OBJECT_H__

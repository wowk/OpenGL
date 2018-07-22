#include <GLObject.hpp>


GLObject::GLObject(GLObject *parent) :
    mModel(1.0f), mParent(nullptr), mPosition(0.0f)
{}

GLObject::~GLObject()
{}

void GLObject::move(const glm::vec3 & offset)
{
    mPosition += offset;
    mModel = glm::translate(mModel, offset);
}

void GLObject::setPosition(const glm::vec3 &position)
{
    mPosition = position;
    mModel = glm::translate(glm::mat4(1.0f), position);
}

void GLObject::setZOrder(int zOrder)
{}

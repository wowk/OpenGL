#include <GLObject.hpp>


GLObject::GLObject(GLObject *parent)
{
    m_parent = parent;
}

GLObject::~GLObject()
{

}

vec3 GLObject::position() const
{
    return m_position;
}

void GLObject::setPosition(const vec3 &position)
{
    m_position = position;
}

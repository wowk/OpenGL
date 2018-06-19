#include <GLObject.h>


GLObject::GLObject(GLObject *parent)
{
    m_parent = parent;

    onMouseButtonDownEvent = nullptr;
    onMouseButtonUpEvent = nullptr;
    onMouseMotionEvent = nullptr;
    onMouseWheelEvent = nullptr;
    onKeyDownEvent = nullptr;
    onKeyUpEvent = nullptr;
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

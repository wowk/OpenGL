#include <GLCamera.hpp>



GLCamera::GLCamera()
{
    init();
}

bool GLCamera::init()
{
    setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
    setFront(glm::vec3(0.0f, 0.0f, 1.0f));
    setPosition(glm::vec3(0.0f, 0.0f, 0.0f));

    setAspect(800.0f / 600.0f);
    setFovy(45.0f);
    setZNearPane(0.1f);
    setZFarPane(1000.0f);

    setMinPitch(-89.0f);
    setMaxPitch(89.0f);

    m_modelMatrix = glm::rotate(m_modelMatrix, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));
}

void GLCamera::draw()
{
}

void GLCamera::update(GLfloat delta)
{
    m_viewMatrix = glm::lookAt(m_position, m_position + m_front, m_worldUp);
}

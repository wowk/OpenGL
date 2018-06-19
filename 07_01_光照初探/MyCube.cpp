#include <MyCube.hpp>


bool MyCube::init()
{
    GLfloat vertices[] = {
        -0.5f,  -0.5f,  -0.5f,
        -0.5f,  -0.5f,  0.5f,
        0.5f,   -0.5f,  0.5f,
        0.5f,   -0.5f,  -0.5f,

        -0.5f,  0.5f,   -0.5f,
        -0.5f,  0.5f,   0.5f,
        0.5f,   0.5f,   0.5f,
        0.5f,   0.5f,   -0.5f,
    };

    GLuint indices[] = {
        0,  1,  2,      0,  3,  2,
        0,  4,  5,      0,  1,  5,
        0,  4,  7,      0,  3,  7,
        6,  5,  4,      6,  7,  4,
        6,  5,  1,      6,  2,  1,
        6,  2,  3,      6,  7,  3,
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)NULL);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)NULL);
    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
//    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void MyCube::bind()
{
    if( m_vao > 0 )
        glBindVertexArray(m_vao);
}

void MyCube::draw()
{
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

#include <MyGlass.hpp>

MyGlass::MyGlass()
{}

MyGlass::~MyGlass()
{
    if( veo > 0 ){
        glDeleteBuffers(1, &veo);
    }
    if( vbo > 0 ){
        glDeleteBuffers(1, &vbo);
    }
    if( vao > 0 ){
        glDeleteVertexArrays(1, &vao);
    }
}

bool MyGlass::init()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GLfloat vertices[] = {
        1.0f,   1.0f,   0.0f,   0.0f, 0.0f, 1.0f,   1.0f,   1.0f,
        -1.0f,  1.0f,   0.0f,   0.0f, 0.0f, 1.0f,   0.0f,   1.0f,
        -1.0f,  -1.0f,  0.0f,   0.0f, 0.0f, 1.0f,   0.0f,   0.0f,
        1.0f,   -1.0f,  0.0f,   0.0f, 0.0f, 1.0f,   1.0f,   0.0f,
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    GLuint indices[] = {
        0,  1,  2,
        3,  0,  2,
    };
    glGenBuffers(1, &veo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    glBindVertexArray(0);

    texture.create(GL_TEXTURE_2D);
    texture.use();
    texture.setWrapType();
    texture.setFilter();
    texture.loadImage2D("resources/images/transparent_window.png");
    texture.generateMipmap();
    texture.use(false);
}

void MyGlass::draw(GLShader & shader)
{
    shader.use();
    texture.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);
    texture.use(false);
    shader.use(false);
}

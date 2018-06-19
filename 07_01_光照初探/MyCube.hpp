#ifndef MY_GL_CUBE_H__
#define MY_GL_CUBE_H__

#include <GLTexture.hpp>
#include <GLShader.hpp>
#include <GLObject.hpp>
#include <glad/glad.h>

class MyCube : public GLObject {
public:
    explicit MyCube() {
        init();
    }

    bool init();
    void update(GLfloat delta);
    void bind();
    void draw();

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

#endif//MY_GL_CUBE_H__

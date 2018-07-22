#ifndef MY_GLASS_H__
#define MY_GLASS_H__

#include <glad/glad.h>
#include <GLObject.hpp>
#include <GLShader.hpp>
#include <GLTexture.hpp>


class MyGlass : public GLObject {
public:
    explicit MyGlass();
    ~MyGlass();
    void draw(GLShader & shader);
    bool init();

private:
    GLuint vao;
    GLuint vbo;
    GLuint veo;
    GLTexture texture;
};

#endif//MY_GLASS_H__
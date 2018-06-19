#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <GLCamera.hpp>
#include <GLScene.hpp>
#include <GLShader.hpp>
#include <GLTexture.hpp>
#include <glm/vec3.hpp>


class MyGLScene : public GLScene {
public:
    bool init();
    void update(GLfloat delta);
    void draw();
    ~MyGLScene();

private:
    GLuint vao[2];
    GLuint vbo[2];
    GLuint program;
    GLShader shader;
    GLTexture texture;
    GLint tex1Location;
    GLfloat rotate;
    GLint projLoc;
    GLint modelLoc;
    GLint viewLoc;
    GLfloat radius;
    GLfloat angle;
    GLCamera camera;
};

#endif//MY_GL_SCENE_H__

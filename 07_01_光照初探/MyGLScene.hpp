#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <MyCube.hpp>
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
    GLuint program;
    GLShader shader;
    GLTexture texture;
    GLint tex1Location;
    GLfloat rotate;
    GLint projLoc;
    GLint modelLoc;
    GLint viewLoc;
    GLint surfaceColorLoc;
    GLfloat radius;
    GLfloat angle;
    GLCamera camera;
    MyCube cube;
};

#endif//MY_GL_SCENE_H__

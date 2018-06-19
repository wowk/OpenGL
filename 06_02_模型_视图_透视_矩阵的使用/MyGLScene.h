#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <GLScene.h>
#include <GLShader.h>
#include <GLTexture.h>
#include <glm/vec3.hpp>


class MyGLScene : public GLScene {
public:
    bool init();
    void update(GLfloat delta);
    void draw();
    ~MyGLScene();

private:
    GLuint vao;
    GLuint vbo;
    GLuint program;
    GLShader shader;
    GLTexture texture;
    GLint tex1Location;
    vec3 moveOffset;
    GLfloat rotate;
    GLint projLoc;
    GLint modelLoc;
    GLint viewLoc;
    glm::vec3 viewCamera;
    glm::vec3 posCamera;
};

#endif//MY_GL_SCENE_H__

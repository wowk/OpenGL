#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <MyCube.hpp>
#include <GLCamera.hpp>
#include <GLScene.hpp>
#include <GLShader.hpp>
#include <GLTexture.hpp>
#include <glm/vec3.hpp>
#include <map>


class MyGLScene : public GLScene {
public:
    bool init();
    void update(GLfloat delta);
    void draw();
    ~MyGLScene();

private:
    GLTexture texture;
    GLfloat rotate;
    GLfloat radius;
    GLfloat angle;
    GLCamera camera;
    GLShader shaderCube;
    GLShader shaderLight;
    MyCube cube;
    MyCube light;
    GLfloat ambientStrength;
    std::map<SDL_Keycode, bool> m_keymap;
};

#endif//MY_GL_SCENE_H__

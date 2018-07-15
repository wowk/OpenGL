#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <GLModel.hpp>
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
    GLCamera camera;
    GLShader shader;
    GLModel* model;
    std::map<GLuint,bool> keyMap;
    std::map<GLuint,bool> mouseMap;
};

#endif//MY_GL_SCENE_H__

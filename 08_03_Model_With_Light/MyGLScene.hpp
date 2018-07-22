#ifndef MY_GL_SCENE_H__
#define MY_GL_SCENE_H__

#include <MyGlass.hpp>
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
    GLShader modelShader;
    GLShader sunShader;
    GLModel* female;
    GLModel* model;
    GLModel* sun;
    std::map<GLuint,bool> keyMap;
    std::map<GLuint,bool> mouseMap;
    MyGlass glass[3];
};

#endif//MY_GL_SCENE_H__

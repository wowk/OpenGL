#include <GLScene.hpp>


GLScene::GLScene()
{
    onMouseButtonDownEvent = nullptr;
    onMouseButtonUpEvent = nullptr;
    onMouseMotionEvent = nullptr;
    onMouseWheelEvent = nullptr;
    onKeyDownEvent = nullptr;
    onKeyUpEvent = nullptr;
}

GLScene::~GLScene()
{

}

void GLScene::update(GLfloat delta)
{

}

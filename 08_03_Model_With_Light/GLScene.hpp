#ifndef GL_SCENE_H__
#define GL_SCENE_H__

#include <glad/glad.h>
#include <GLObject.hpp>
#include <functional>


using std::function;
using std::bind;


class GLScene : public GLObject {
public:
    GLScene();

    function<void(const SDL_KeyboardEvent*)> onKeyUpEvent;
    function<void(const SDL_KeyboardEvent*)> onKeyDownEvent;
    function<void(const SDL_MouseButtonEvent*)> onMouseButtonDownEvent;
    function<void(const SDL_MouseButtonEvent*)> onMouseButtonUpEvent;
    function<void(const SDL_MouseWheelEvent*)> onMouseWheelEvent;
    function<void(const SDL_MouseMotionEvent*)> onMouseMotionEvent;
public:
    virtual ~GLScene();
    virtual void update(GLfloat delta);
};

#endif//GL_SCENE_H__

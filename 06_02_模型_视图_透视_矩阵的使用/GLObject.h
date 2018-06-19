#ifndef GL_OBJECT_H__
#define GL_OBJECT_H__

#include <glm/vec3.hpp>
#include <SDL2/SDL.h>
#include <functional>

using std::function;
using std::bind;
using glm::vec3;


class GLObject {
public:
    explicit GLObject(GLObject* parent = nullptr);
    virtual bool init() = 0;
    virtual ~GLObject();

    virtual void draw(){}

public:
    function<void(const SDL_KeyboardEvent*)> onKeyUpEvent;
    function<void(const SDL_KeyboardEvent*)> onKeyDownEvent;
    function<void(const SDL_MouseButtonEvent*)> onMouseButtonDownEvent;
    function<void(const SDL_MouseButtonEvent*)> onMouseButtonUpEvent;
    function<void(const SDL_MouseWheelEvent*)> onMouseWheelEvent;
    function<void(const SDL_MouseMotionEvent*)> onMouseMotionEvent;

    vec3 position() const;
    void setPosition(const vec3 &position);

private:
    GLObject* m_parent;
    vec3 m_position;
};

#endif//GL_OBJECT_H__

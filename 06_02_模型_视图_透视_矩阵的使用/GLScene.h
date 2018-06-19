#ifndef GL_SCENE_H__
#define GL_SCENE_H__

#include <glad/glad.h>
#include <GLObject.h>

class GLScene : public GLObject {
public:

    virtual ~GLScene();
    virtual void update(GLfloat delta);
};

#endif//GL_SCENE_H__

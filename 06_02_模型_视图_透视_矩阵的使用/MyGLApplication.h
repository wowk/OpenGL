#ifndef MY_GL_APPLICATION_H__
#define MY_GL_APPLICATION_H__

#include <glad/glad.h>
#include <GLApplication.h>

class MyGLApplication : public GLApplication {
public:
    static GLApplication* create();
    virtual bool init(int argc, char* argv[]);
};

#endif//MY_GL_APPLICATION_H__

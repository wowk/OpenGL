#ifndef MY_GL_APPLICATION_H__
#define MY_GL_APPLICATION_H__

#include <glad/glad.h>
#include <GLApplication.hpp>

class MyGLApplication : public GLApplication {
private:
    explicit MyGLApplication();
    ~MyGLApplication();

public:
    static GLApplication* create();
    virtual bool init(int argc, char* argv[]);
};

#endif//MY_GL_APPLICATION_H__

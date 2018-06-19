#ifndef GL_APPLICATION_H__
#define GL_APPLICATION_H__

#include <GLScene.hpp>
#include <glad/glad.h>
#include <stack>
#include <SDL2/SDL.h>



using std::stack;



class GLApplication {
protected:
    explicit GLApplication();

public:
    static GLApplication* create();

    virtual bool init(int argc, char* argv[]);
    virtual void draw();
    virtual void update(GLfloat delta);
    virtual void close();
    virtual void handleInput(const SDL_Event* e);
    virtual ~GLApplication();

    void mainloop();

    bool running() const;
    void setRunning(const bool & running);

    GLScene *currentScene();
    GLScene* popScene();
    void pushScene(GLScene*);
    void runScene(GLScene*);

    static GLApplication *inst();
    static void setInst(GLApplication *value);

private:
    bool m_running;
    SDL_GLContext m_gl_context;
    SDL_Window* m_window;
    stack<GLScene*> m_stack;

    static GLApplication* m_inst;
};



#endif//GL_APPLICATION_H__

#include <GLApplication.hpp>
#include <GLScene.hpp>
#include <cassert>
#include <iostream>
#include <SDL2/SDL_image.h>


using std::cout;
using std::cerr;
using std::endl;

GLApplication* GLApplication::m_inst = nullptr;

void GLApplication::mainloop()
{
    GLfloat delta;
    GLuint ticks;
    GLuint oldTicks;
    GLfloat frameTime;
    SDL_Event event;

    oldTicks = SDL_GetTicks();
    setRunning(true);
    while (running()) {
        ticks = SDL_GetTicks();
        frameTime = ticks - oldTicks;
        while (frameTime > 0.0) {
            while( SDL_PollEvent(&event) ) {
                handleInput(&event);
            }
            if( frameTime > m_timePerFrame ){
                delta = m_timePerFrame / 1000.f;
            }else{
                delta = frameTime / 1000.0f;
            }
            currentScene()->update(delta);
            frameTime -= m_timePerFrame;
        }
        draw();
    }
}

GLApplication::GLApplication()
{
    setFrameRate(300);
}

bool GLApplication::init(int argc, char* argv[])
{
    if( 0 > SDL_Init(SDL_INIT_EVERYTHING) ){
        cerr << "SDL_Init(Everything) failed: " << SDL_GetError() << endl;
        goto error_SDL_INIT;
    }else if( 0 > IMG_Init(IMG_INIT_PNG|IMG_INIT_JPG) ){
        cerr << "IMG_Init(Everything) failed: " << IMG_GetError() << endl;
        goto error_IMG_INIT;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    m_window = SDL_CreateWindow(basename(argv[0]), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            800, 600, SDL_WINDOW_OPENGL);
    if( !m_window ){
        cerr << "SDL_CreateWindow failed: " << SDL_GetError() << endl;
        goto error_SDL_CREATE_WINDOW;
    }

    m_gl_context = SDL_GL_CreateContext(m_window);
    if( !m_gl_context ){
        cerr << "SDL_GL_CreateContext failed: " << SDL_GetError() << endl;
        goto error_SDL_GL_CREATE_CONTEXT;
    }

    if( 0 == gladLoadGLLoader(SDL_GL_GetProcAddress) ){
        cerr << "gladLoadGLLoaderfailed: " << endl;
        goto error_GLAD_LOAD_GL_LOADER;
    }

    SDL_SetRelativeMouseMode(SDL_TRUE);

    glEnable(GL_DEPTH_TEST);

    return true;

error_GLAD_LOAD_GL_LOADER:
    SDL_GL_DeleteContext(m_gl_context);
    m_gl_context = nullptr;

error_SDL_GL_CREATE_CONTEXT:
    SDL_DestroyWindow(m_window);
    m_window = nullptr;

error_SDL_CREATE_WINDOW:
    IMG_Quit();

error_IMG_INIT:
    SDL_Quit();

error_SDL_INIT:
    return false;

}

void GLApplication::draw()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);
    glClearColor(0x63/255.0, 0xa5/255.0, 0xe0/255.0f, 1.0f);
    currentScene()->draw();
    SDL_GL_SwapWindow(m_window);
}

void GLApplication::update(GLfloat delta)
{
    if( currentScene() )
        currentScene()->update(delta);
}

void GLApplication::close()
{
    setRunning(false);
}

void GLApplication::handleInput(const SDL_Event *e)
{
    switch (e->type) {
    case SDL_KEYDOWN:
        if( currentScene() && currentScene()->onKeyDownEvent ){
            currentScene()->onKeyDownEvent(&e->key);
        }
        break;

    case SDL_KEYUP:
        if( currentScene() && currentScene()->onKeyUpEvent ){
            currentScene()->onKeyUpEvent(&e->key);
        }
        break;

    case SDL_MOUSEBUTTONDOWN:
        if( currentScene() && currentScene()->onMouseButtonDownEvent ){
            currentScene()->onMouseButtonDownEvent(&e->button);
        }
        break;

    case SDL_MOUSEBUTTONUP:
        if( currentScene() && currentScene()->onMouseButtonUpEvent ){
            currentScene()->onMouseButtonUpEvent(&e->button);
        }
        break;

    case SDL_MOUSEMOTION:
        if( currentScene() && currentScene()->onMouseMotionEvent ){
            currentScene()->onMouseMotionEvent(&e->motion);
        }
        break;

    case SDL_MOUSEWHEEL:
        if( currentScene() && currentScene()->onMouseWheelEvent ){
            currentScene()->onMouseWheelEvent(&e->wheel);
        }
        break;

//    case SDL_QUIT:
//        GLApplication::inst()->close();
//        break;

    default:
        break;
    }
}

GLApplication::~GLApplication()
{
    setRunning(false);
    std::cout << "stop running" << std::endl;
    SDL_GL_DeleteContext(m_gl_context);
    std::cout << "delete GL context" << std::endl;
    SDL_DestroyWindow(m_window);
    std::cout << "destroy SDL window" << std::endl;
    IMG_Quit();
    std::cout << "Unload IMG Library" << std::endl;
    SDL_Quit();
    std::cout << "Unload SDL Library" << std::endl;
}

bool GLApplication::running() const
{
    return m_running;
}

void GLApplication::setRunning(const bool &running)
{
    m_running = running;
}

void GLApplication::pushScene(GLScene * scene)
{
    assert(scene);
    m_stack.push(scene);
}

void GLApplication::runScene(GLScene * scene)
{
    m_stack.push(scene);
}

GLApplication *GLApplication::inst()
{
    return m_inst;
}

void GLApplication::setInst(GLApplication *value)
{
    m_inst = value;
}

void GLApplication::setFrameRate(const GLuint &frameRate)
{
    m_frameRate = frameRate;
    m_timePerFrame = 1000.0 / m_frameRate;
}

GLScene* GLApplication::popScene()
{
    auto ptr = m_stack.empty() ? nullptr : m_stack.top();

    m_stack.pop();

    return ptr;
}

GLScene *GLApplication::currentScene()
{
    return m_stack.empty() ? nullptr : m_stack.top();
}

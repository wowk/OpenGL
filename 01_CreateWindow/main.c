#include <stdio.h>
#include "glad/glad.h"
#include <SDL2/SDL.h>


int main(int argc, char** argv)
{
    GLboolean running;
    SDL_Window* window = NULL;
    SDL_GLContext glContext = NULL;

    if( SDL_Init(SDL_INIT_VIDEO) < 0 ){
        printf("init SDL(Video) failed: %s\n", SDL_GetError());
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(argv[0], 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    if( !window ){
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        goto error_create_window;
    }

    glContext = SDL_GL_CreateContext(window);
    if( glContext == NULL ){
        printf("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        goto error_gl_create_context;
    }

    if( gladLoadGLLoader(SDL_GL_GetProcAddress) == 0 ){
        printf("init glad failed\n");
        goto error_glad;
    }

    running = GL_TRUE;
    while ( running) {
        SDL_Event event;
        while (SDL_PollEvent(&event) ) {
            if( event.type == SDL_KEYDOWN ){
                running = GL_FALSE;
                break;
            }
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
    }


    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;


error_glad:
    SDL_GL_DeleteContext(glContext);
error_gl_create_context:
    SDL_DestroyWindow(window);
error_create_window:
    SDL_Quit();

    return -1;
}

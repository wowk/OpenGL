#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    atexit(SDL_Quit);

    SDL_Window *window;
    SDL_Renderer *renderer;
    Uint32 wflags = SDL_WINDOW_OPENGL|SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_RESIZABLE;
    if(0 > SDL_CreateWindowAndRenderer(800, 600, wflags, &window, &renderer)) {
        cerr << "failed to create window" << endl;
        return -errno;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);

    if(!gladLoadGL()) {
        cerr << "failed to load GL library" << endl;
        SDL_GL_DeleteContext(glContext);
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        return -errno;
    }

    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);
    glViewport(0, 0, windowWidth, windowHeight);

    bool running = true;
    SDL_Event event;
    while(running) {
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                running = false;
            }else if(event.type == SDL_WINDOWEVENT) {
                if(event.window.event == SDL_WINDOWEVENT_RESIZED) {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                }
            }
        }

        glClearColor(0.3f, 0.2f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);

    return 0;
}

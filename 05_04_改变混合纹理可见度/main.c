#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


#define WORKDIR "../05_04_改变混合纹理可见度/"

GLsizei loadFile(const char* fileName, GLchar* buffer, GLsizei* bufferLen)
{
    size_t ret;
    long fileLen;
    FILE* fp = NULL;

    assert( fileName && buffer );

    fp = fopen(fileName, "r");
    if( !fp ){
        printf("fopen(%s, r) failed: %s\n", fileName, strerror(errno));
        return 0;
    }

    fseek(fp, 0, SEEK_END);
    fileLen = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    if( fileLen < 0 ){
        fclose(fp);
        printf("ftell(%s, r) failed: %s\n", fileName, strerror(errno));
        return 0;
    }else if( fileLen > *bufferLen ){
        fclose(fp);
        printf("buffer is too small: at lease %ld bytes\n", fileLen);
        return 0;
    }

    ret = fread(buffer, (size_t)fileLen, 1, fp);
    if( ret < 1 ){
        fclose(fp);
        printf("fread failed: read part data\n");
        return 0;
    }

    fclose(fp);
    buffer[fileLen] = 0;
    *bufferLen = (GLsizei)fileLen;

    return *bufferLen;
}


int main(int argc, char *argv[])
{
    GLuint vao;
    GLuint vbo;
    GLfloat vertices[] = {
        1.0f,   -1.0f,  0.0f,   2.0f,  0.0f,
        -1.0f,  -1.0f,  0.0f,   0.0f,  0.0f,
        -1.0f,  1.0f,   0.0f,   0.0f,  2.0f,
        1.0f,   1.0f,   0.0f,   2.0f,  2.0f,
    };

    GLuint indices[] = {
        0,  1,  2,
        0,  3,  2,
    };



    GLfloat colorUniform[3];
    GLint colorUniformLocation;

    GLfloat moveOffsetUniform[2];
    GLint moveOffsetUniformLocation;

    GLfloat alpha = 0.5f;
    GLint alphaLocation;

    GLuint texture[2];
    GLint textureLocation[2];

    SDL_Surface* image;

    GLint status;
    GLuint vertexShader;
    GLuint fragmentShader;
    GLuint program;
    GLchar *pbuffer;
    GLchar buffer[4096];
    GLsizei bufferLen;
    GLchar logBuffer[256];
    GLsizei logBufferLen;

    GLboolean running = GL_FALSE;
    SDL_Window* window = NULL;
    SDL_GLContext glContext = NULL;

    chdir(WORKDIR);

    if( 0 > SDL_Init(SDL_INIT_VIDEO) ){
        printf("SDL_Init(Video) failed: %s\n", SDL_GetError());
        goto error_sdl_init;
    }

    if( 0 > IMG_Init(IMG_INIT_JPG|IMG_INIT_PNG|IMG_INIT_TIF|IMG_INIT_WEBP) ){
        printf("IMG_Init(ALL) failed: %s\n", IMG_GetError());
        goto error_img_init;
    }

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow(argv[0], 100, 100, 800, 600, SDL_WINDOW_OPENGL);
    if( !window ){
        printf("SDL_CreateWindow failed: %s\n", SDL_GetError());
        goto error_sdl_create_window;
    }

    glContext = SDL_GL_CreateContext(window);
    if( !glContext ){
        printf("SDL_GL_CreateContext failed: %s\n", SDL_GetError());
        goto error_sdl_gl_create_context;
    }

    if( 0 == gladLoadGLLoader(SDL_GL_GetProcAddress) ){
        printf("gladLoadGLLoader failed\n");
        goto error_glad_load_error;
    }

    /* load vertex data */
    glGenVertexArrays(1, &vao);
    if( 0 == vao ){
        printf("glGenVertexArrays failed: %d\n", glGetError());
        goto error_gl_gen_vertex_arrays;
    }
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    if( 0 == vbo ){
        printf("glGenBuffers failed: %d\n", glGetError());
        goto error_gl_gen_buffers;
    }
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

    program = glCreateProgram();
    if( 0 == program ){
        printf("glCreateProgram failed: %d\n", glGetError());
        goto error_gl_create_program;
    }

    /* load vertex shader */
    bufferLen = sizeof(buffer);
    if( 0 == loadFile("shader.vert", buffer, &bufferLen) ){
        goto error_load_vertex_source;
    }

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    if( 0 == vertexShader ){
        goto error_gl_create_vertex_shader;
    }

    pbuffer = buffer;
    glShaderSource(vertexShader, 1, &pbuffer, &bufferLen);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if( 0 == status ){
        glGetShaderInfoLog(vertexShader, sizeof(logBuffer), &logBufferLen, logBuffer);
        printf("compile shader failed:\n%s\nerror: %s\n", buffer, logBuffer);
        goto error_gl_compile_shader;
    }
    glAttachShader(program, vertexShader);
    glDeleteShader(vertexShader);
    vertexShader = 0;

    /* load fragment shader */
    bufferLen = sizeof(buffer);
    if( 0 == loadFile("shader.frag", buffer, &bufferLen) ){
        goto error_load_fragment_source;
    }

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if( 0 == fragmentShader ){
        goto error_gl_create_fragment_shader;
    }

    pbuffer = buffer;
    glShaderSource(fragmentShader, 1, &pbuffer, &bufferLen);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if( 0 == status ){
        glGetShaderInfoLog(fragmentShader, sizeof(logBuffer), &logBufferLen, logBuffer);
        printf("compile shader failed:\n%s\nerror: %s\n", buffer, logBuffer);
        goto error_gl_compile_fragment_shader;
    }
    glAttachShader(program, fragmentShader);

    /* link program */
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if( 0 == status ){
        glGetProgramInfoLog(program, sizeof(logBuffer), &logBufferLen, logBuffer);
        printf("link program failed: %s\n", logBuffer);
        goto error_link_program;
    }

    colorUniformLocation = glGetUniformLocation(program, "vertColor");
    if( -1 == colorUniformLocation ){
        printf("get uniform <vertColor>'s location failed: %d\n", glGetError());
        goto error_get_uniform_vertColor_location;
    }
    glGetUniformfv(program, colorUniformLocation, colorUniform);

    moveOffsetUniformLocation = glGetUniformLocation(program, "moveOffset");
    if( -1 == moveOffsetUniformLocation ){
        printf("get uniform <moveOffset>'s location failed: %d\n", glGetError());
        goto error_get_uniform_moveOffset_location;
    }
    glGetUniformfv(program, moveOffsetUniformLocation, moveOffsetUniform);

    glGenTextures(2, texture);
    if( 0 == texture[0] ){
        printf("glGentexture failed: %d\n", glGetError());
        goto error_gl_gen_textures;
    }

    alphaLocation = glGetUniformLocation(program, "alpha");
    if( -1 == alphaLocation ){
        printf("get uniform <alpha>'s location failed: %d\n", glGetError());
        goto error_gl_get_uniform_alpha_location;
    }

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    image = IMG_Load("texture1.jpg");
    if( !image ){
        printf("IMG_Load(texture1.jpg) failed: %s\n", IMG_GetError());
        goto error_img_load_texture1_jpg;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    SDL_FreeSurface(image);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    image = IMG_Load("texture2.jpg");
    if( !image ){
        printf("IMG_Load(texture2.jpg) failed: %s\n", IMG_GetError());
        goto error_img_load_texture2_jpg;
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    SDL_FreeSurface(image);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);

    textureLocation[0] = glGetUniformLocation(program, "texture1Sampler2D");
    textureLocation[1] = glGetUniformLocation(program, "texture2Sampler2D");
    if( -1 == textureLocation[0] || -1 == textureLocation[1] ){
        printf("get sampler2D location: %d\n", glGetError());
        goto error_gl_get_uniform_texture_sampler2d;
    }

    running = GL_TRUE;
    while( running ){
        SDL_Event event;
        while( SDL_PollEvent(&event)){
            if( event.type == SDL_KEYDOWN ){
                switch(event.key.keysym.sym){
                case SDLK_1:
                    if( colorUniform[0] > 0.0f )
                        colorUniform[0] -= 0.05f;
                    break;
                case SDLK_2:
                    if( colorUniform[0] < 1.0f )
                        colorUniform[0] += 0.05f;
                    break;
                case SDLK_3:
                    if( colorUniform[1] > 0.0f )
                        colorUniform[1] -= 0.05f;
                    break;
                case SDLK_4:
                    if( colorUniform[1] < 1.0f )
                        colorUniform[1] += 0.05f;
                    break;
                case SDLK_5:
                    if( colorUniform[2] > 0.0f )
                        colorUniform[2] -= 0.05f;
                    break;
                case SDLK_6:
                    if( colorUniform[2] < 1.0f )
                        colorUniform[2] += 0.05f;
                    break;

                case SDLK_UP:
                    moveOffsetUniform[1] += 0.1f;
                    break;
                case SDLK_DOWN:
                    moveOffsetUniform[1] -= 0.1f;
                    break;
                case SDLK_LEFT:
                    moveOffsetUniform[0] -= 0.1f;
                    break;
                case SDLK_RIGHT:
                    moveOffsetUniform[0] += 0.1f;
                    break;

                default:
                    printf("quit\n");
                    running = GL_FALSE;
                    break;
                }
            }else if( event.type == SDL_MOUSEWHEEL ){
                if( event.wheel.y < 0 ){
                    if( alpha > 0.0f ){
                        alpha += event.wheel.y / 50.0f;
                    }else{
                        alpha = 0.0f;
                    }
                }else{
                    if( alpha < 1.0f ){
                        alpha += event.wheel.y / 50.0f;
                    }else{
                        alpha = 1.0f;
                    }
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glActiveTexture(GL_TEXTURE0);
        glUniform1i(textureLocation[0], 0);
        glBindTexture(GL_TEXTURE_2D, texture[0]);
        glActiveTexture(GL_TEXTURE1);
        glUniform1i(textureLocation[1], 1);
        glBindTexture(GL_TEXTURE_2D, texture[1]);

        glUniform3fv(colorUniformLocation, 1, colorUniform);
        glUniform2fv(moveOffsetUniformLocation, 1, moveOffsetUniform);
        glUniform1f(alphaLocation, alpha);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_INT, indices);
        glBindVertexArray(0);

        glUseProgram(0);

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);

        SDL_GL_SwapWindow(window);
    }

    glDeleteTextures(2, texture);
    glDeleteProgram(program);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;

error_img_load_texture2_jpg:
error_img_load_texture1_jpg:
    glDeleteTextures(2, texture);
error_gl_gen_textures:
error_gl_get_uniform_texture_sampler2d:
error_get_uniform_moveOffset_location:
error_get_uniform_vertColor_location:
error_gl_get_uniform_alpha_location:
error_link_program:
error_gl_compile_fragment_shader:
    if( fragmentShader )
        glDeleteShader(fragmentShader);
error_gl_create_fragment_shader:
error_load_fragment_source:
error_gl_compile_shader:
    if( vertexShader )
        glDeleteShader(vertexShader);
error_gl_create_vertex_shader:
error_load_vertex_source:
    glDeleteProgram(program);
error_gl_create_program:
    glDeleteBuffers(1, &vbo);
error_gl_gen_buffers:
    glDeleteVertexArrays(1, &vao);
error_gl_gen_vertex_arrays:
error_glad_load_error:
    SDL_GL_DeleteContext(glContext);
error_sdl_gl_create_context:
    SDL_DestroyWindow(window);
error_sdl_create_window:
    IMG_Quit();
error_img_init:
    SDL_Quit();
error_sdl_init:

    return -1;
}

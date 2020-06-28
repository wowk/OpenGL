#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

const string loadFile(const string & filename) {
    fstream fin(filename, ios_base::in);
    size_t filesize = fin.seekg(0, ios_base::end).tellg();

    string data;
    char buffer[filesize+1];
    if((fstream::pos_type)filesize != fin.seekg(0, ios_base::beg).readsome(buffer, 4096)) {
        cerr << "failed to read the whole file content: "  << strerror(errno) << endl;
        return data;
    }
    buffer[filesize] = 0;
    data = buffer;

    return data;
}

class GLLight {};

class GLDirectLight {};

class GLSpotLight {};

class GLMaterial {};

class GLMesh {};

class GLModel {};

class GLCamera {

};

class GLTexture {

};

class GLUniform {

};

class GLShader {
public:
    GLShader() : m_shader(0) {}

    void loadFromString(const string & source, GLenum type) {
        GLint length = 1;
        GLuint shader = glCreateShader(type);
        if(!shader) {
            cerr << "failed to loadShader" << endl;
            return;
        }

        GLchar *shaderSources[] = {(GLchar*)source.c_str()};
        glShaderSource(shader, 1, shaderSources, NULL);

        GLint compile_status;
        glCompileShader(shader);
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

        if(compile_status == GL_FALSE) {
            GLsizei length;
            GLchar buffer[1024];
            glGetShaderInfoLog(shader, sizeof(buffer), &length, buffer);
            glDeleteShader(shader);
            buffer[length] = 0;
            cerr << "Compile Shader Error" << (char*)buffer << endl;
        }
        m_shader = shader;
    }

    bool createProgram() {
        bool result = (m_program = glCreateProgram());
        if(result) {
            cerr << "failed to create program" << endl;
        }
        return result;
    }

    bool linkProgram() {

    }

    void attach() {
        glAttachShader(m_program, m_shader);
    }

    void loadFromFile(const string & filename, GLenum type) {
        loadFromString(loadFile(filename), type);
    }

    void loadFragmentShader(const string & filename) {

    }

private:
    GLuint m_shader;
    GLuint m_program;
};

class GLProgram {
public:
    GLProgram(GLShader & shader) : m_shader(shader) {
        m_shader.get();
    }

    ~GLProgram() {
        m_shader.put();
    }

private:
    GLShader & m_shader;
};

class GLObject {
public:
    GLObject(GLuint vao, GLuint vbo, GLuint ebo = 0) {}
    GLObject() {
        glGenBuffers(1, &m_vbo);
        glGenVertexArrays(1, &m_vao);
    }

    void bufferData(GLvoid *data,  GLsizei size, GLsizei vsize,GLenum type = GL_STATIC_DRAW) {
        glBindVertexArray(m_vao);
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, size, data, type);
        glVertexAttribPointer(0, vsize, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (GLvoid*)0);
    }

private:
    GLuint m_vao;
    GLuint m_vbo;
    GLuint m_ebo;
};

class GLSprite : public GLObject {

};

class GLApplication {
public:
    bool init(const char *title, int w, int h, int wflag = 0,
             int glMajor = 3, int glMinor = 3, int glProfile = SDL_GL_CONTEXT_PROFILE_CORE)
    {
        SDL_Init(SDL_INIT_EVERYTHING);

        wflag |= SDL_WINDOW_OPENGL;
        SDL_CreateWindowAndRenderer(w, h, wflag, &m_window, &m_renderer);
        SDL_SetWindowTitle(m_window, title);

        m_glContext = SDL_GL_CreateContext(m_window);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, glMajor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, glMinor);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, glProfile);

        if(!gladLoadGL()) {
            SDL_Quit();
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
            cerr << "failed to load GL library" << endl;
            return false;
        }

        glViewport(0, 0, w, h);

        return true;
    }

    virtual void draw() = 0;
    virtual void processEvent(const SDL_Event *event) = 0;

    void setRunning(bool running) {
        m_running = running;
    }

    virtual void run(void) {
        SDL_Event event;
        setRunning(true);
        while (m_running) {
            while (SDL_PollEvent(&event)) {
                processEvent(&event);
            }
            glClearColor(0.0f, 0.0f, 0.0f, 255.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            draw();

            SDL_GL_SwapWindow(m_window);
        }
    }

    ~GLApplication() {
        if(m_window) {
            SDL_GL_DeleteContext(m_glContext);
            SDL_DestroyWindow(m_window);
            SDL_DestroyRenderer(m_renderer);
        }
    }

private:
    bool m_running;
    SDL_GLContext   m_glContext;
    SDL_Window      *m_window;
    SDL_Renderer    *m_renderer;
};

class MyGLApplication : public GLApplication {
public:
    MyGLApplication(const char *title, int w, int h) {
        this->init(title, w, h);
    }

    void processEvent(const SDL_Event *event) {
        switch (event->type) {
        case SDL_QUIT:
            setRunning(false);
            break;
        case SDL_WINDOWEVENT:
            switch (event->window.event) {
            case SDL_WINDOWEVENT_CLOSE:
                setRunning(false);
                break;
            default:
                break;
            }
        default:
            break;
        }
    }

    void draw(void) {

    }
};

int main()
{
    MyGLApplication app("Hello, Triangle", 800, 600);

    GLuint vbo, ebo;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    GLfloat vertices[] = {
        -1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
    };

    cout << loadFile("../01_02_Create_A_Triangle/vertex.vert") << endl;
    cout << loadFile("../01_02_Create_A_Triangle/fragment.frag") << endl;

    app.run();

    return 0;
}

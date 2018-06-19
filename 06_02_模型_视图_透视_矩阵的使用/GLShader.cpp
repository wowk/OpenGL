#include <GLShader.h>
#include <Utils/FileUtil.h>
#include <iostream>

using std::cout;
using std::endl;


bool GLShader::loadShader(GLuint type, const string &shaderSource)
{
    if( type == GL_VERTEX_SHADER ){
        m_vertShaders.push_back(shaderSource);
    }else if( type == GL_FRAGMENT_SHADER ){
        m_fragShaders.push_back(shaderSource);
    }else{
        cout << "ShaderSource type is not supported" << endl;
        return false;
    }

    return true;
}

bool GLShader::loadShaderFile(GLuint type, const string &file)
{
    string content;
    if( !FileUtil::loadFile(file, content) ){
        return false;
    }

    return loadShader(type, content);
}

bool GLShader::compile()
{
    GLint status;

    if( m_vertShaders.size() ){
        size_t sourceCount = m_vertShaders.size();
        const GLchar* sources[sourceCount];
        GLint sourceLens[sourceCount];

        for( size_t i = 0 ; i < sourceCount ; i ++ ){
            sources[i] = static_cast<const GLchar*>(m_vertShaders[i].c_str());
            sourceLens[i] = static_cast<GLint>(m_vertShaders[i].size());
        }

        m_vertShader = glCreateShader(GL_VERTEX_SHADER);
        if( 0 == m_vertShader ){
            cout << "create shader object failed" << endl;
            goto error;
        }

        glShaderSource(m_vertShader, sourceCount, sources, sourceLens);
        glCompileShader(m_vertShader);
        glGetShaderiv(m_vertShader, GL_COMPILE_STATUS, &status);
        if( !status ){
            GLchar log[512] = {0};
            GLsizei logLen;
            glGetShaderInfoLog(m_vertShader, 512, NULL, log);
            cout << "Compile Shader Failed: " << log << endl;
            goto error;
        }
        m_compiled_vshader = true;
    }

    if( m_fragShaders.size() ){
        size_t sourceCount = m_fragShaders.size();
        const GLchar* sources[sourceCount];
        GLint sourceLens[sourceCount];

        for( size_t i = 0 ; i < sourceCount ; i ++ ){
            sources[i] = m_fragShaders[i].c_str();
            sourceLens[i] = static_cast<GLint>(m_fragShaders[i].size());
        }

        m_fragShader = glCreateShader(GL_FRAGMENT_SHADER);
        if( 0 == m_fragShader ){
            cout << "create shader2 object failed" << endl;
            goto error;
        }

        glShaderSource(m_fragShader, sourceCount, sources, sourceLens);
        glCompileShader(m_fragShader);
        glGetShaderiv(m_fragShader, GL_COMPILE_STATUS, &status);
        if( !status ){
            GLchar log[256] = {0};
            GLsizei logLen;
            glGetShaderInfoLog(m_fragShader, sizeof(log), &logLen, log);
            cout << "Compile Shader2 Failed: " << log << endl;
            goto error;
        }
        m_compiled_fshader = true;
    }

    return true;

error:
    if( m_vertShader ){
        glDeleteShader(m_vertShader);
        m_vertShader = 0;
        m_compiled_vshader = false;
    }

    if( m_fragShader ){
        glDeleteShader(m_fragShader);
        m_fragShader = 0;
        m_compiled_fshader = false;
    }

    return false;
}

bool GLShader::createProgram()
{
    if( m_shaderProgram ){
        cout << "program has been exited" << endl;
        return false;
    }

    m_shaderProgram = glCreateProgram();
    if( 0 == m_shaderProgram ){
        cout << "create program failed" << endl;
        return false;
    }

    return true;
}

bool GLShader::attach()
{
    if( 0 == m_shaderProgram ){
        cout << "please create program first" << endl;
        return false;
    }

    if( !m_attached_vshader ){
        m_attached_vshader = true;
        glAttachShader(m_shaderProgram, m_vertShader);
    }

    if( !m_attached_fshader ){
        m_attached_fshader = true;
        glAttachShader(m_shaderProgram, m_fragShader);
    }

    return m_attached_fshader || m_attached_vshader;
}

void GLShader::detach()
{
    if( m_attached_vshader ){
        glDetachShader(m_shaderProgram, m_vertShader);
        m_attached_vshader = false;
    }
    if( m_attached_fshader ){
        glDetachShader(m_shaderProgram, m_fragShader);
        m_attached_fshader = false;
    }
}

bool GLShader::link()
{
    if( 0 == m_shaderProgram ){
        cout << "program is not created yet" << endl;
        return false;
    }

    if( m_linked ){
        cout << "program has been linked" << endl;
        return false;
    }

    m_linked = true;
    glLinkProgram(m_shaderProgram);
    GLint status = 1;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &status);
    if( 0 == status ){
        GLchar log[256] = "";
        GLsizei logLen;
        glGetProgramInfoLog(m_shaderProgram, sizeof(log), &logLen, log);
        cout << "link program failed: " << log << endl;
        freeShader();
        freeProgram();
        return false;
    }

    return true;
}

bool GLShader::use(bool use_it)
{
    if( !use_it ){
        //unbind this program
        if( m_used ){
            glUseProgram(0);
            m_used = false;
        }
        return true;
    }

    if( m_used ){
        cout << "this program is already in use" << endl;
        return false;
    }

    if( !m_linked ){
        cout << "this proram is not linked" << endl;
        return false;
    }

    m_used = true;
    glUseProgram(m_shaderProgram);

    return true;
}

void GLShader::freeShader()
{
    if( m_vertShader ){
        glDeleteShader(m_vertShader);
        m_vertShader = 0;
        m_vertShaders.clear();
        m_compiled_vshader = false;
    }

    if( m_fragShader ){
        glDeleteShader(m_fragShader);
        m_fragShader = 0;
        m_fragShaders.clear();
        m_compiled_fshader = false;
    }
}

void GLShader::freeProgram()
{
    if( m_used )
    if( m_shaderProgram ){
        glDeleteProgram(m_shaderProgram);
        m_shaderProgram = 0;
        m_linked = false;
    }
}

GLuint GLShader::program() const
{
    return m_shaderProgram;
}

GLShader::GLShader()
{
    m_vertShader = 0;
    m_fragShader = 0;
    m_attached_vshader = false;
    m_attached_fshader = false;
    m_used = false;
    m_linked = false;
    m_compiled_vshader = false;
    m_compiled_fshader = false;
    m_shaderProgram = 0;
}

GLShader::~GLShader()
{
    use(false);
    detach();
    freeShader();
    freeProgram();
}

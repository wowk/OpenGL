#include <GLShader.hpp>
#include <Utils.hpp>
#include <iostream>

using std::cout;
using std::endl;

GLShader::GLShader()
{
    id = glCreateProgram();
    if( id == 0 ){
        cout << "glCreateProgram failed: " << glGetError() << endl;
    }
}

GLShader::~GLShader()
{
    free();
}

void GLShader::free()
{
    if( id > 0 ){
        glDeleteProgram(id);
    }
}

bool GLShader::hasShader(GLuint type)
{
    return mLoadedShaders.end() != mLoadedShaders.find(type);
}

bool GLShader::load(GLuint type, const string & shaderFile)
{
    string shaderSource;

    if( !Utils::FileUtils::loadFile(shaderFile, shaderSource) ){
        return false;
    }
    
    GLint status;
    GLuint shaderObj;
    const GLchar* buffer;
    GLsizei bufferLen;

    shaderObj = glCreateShader(type);
    buffer = shaderSource.c_str();
    bufferLen = shaderSource.size();
    glShaderSource(shaderObj, 1, &buffer, &bufferLen);

    glCompileShader(shaderObj);
    glGetShaderiv(shaderObj, GL_COMPILE_STATUS, &status);
    if( 0 == status ){
        GLchar log[256] = "";
        GLsizei logLen;
        glGetShaderInfoLog(shaderObj, sizeof(log) - 1, &logLen, log);
        cout << "Load Shader <" << shaderFile << "> failed" << endl;
        cout << "Error: " << log << endl;
        glDeleteShader(shaderObj);
        return false;
    }

    glAttachShader(id, shaderObj);
    glDeleteShader(shaderObj);

    return true;
}

bool GLShader::link()
{
    GLint status;

    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    if( 0 == status ){
        GLchar log[256] = "";
        GLsizei logLen;
        glGetProgramInfoLog(id, sizeof(log)-1, &logLen, log);
        log[logLen] = '\0';
        cout << "link Program failed: " << log << endl;
        return false;
    }
    
    return true;
}

void GLShader::use(bool used)
{
    if( id > 0 && used ){
        glUseProgram(id);
    }else{
        glUseProgram(0);
    }
}

GLint GLShader::location(const char* uniform)
{
    string uniformName(uniform);

    auto itr = mUniformsLoc.find(uniformName);
    if( itr == mUniformsLoc.end() ){
        GLint loc = glGetUniformLocation(id, uniform);
        if( loc == -1 ){
            cout << "failed to get " << uniform << "'s location" << endl;
            return loc;
        }else{
            mUniformsLoc[uniformName] = loc;
            itr = mUniformsLoc.find(uniformName);
        }
    }
    return itr->second;
}
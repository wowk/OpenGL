#ifndef GL_SHADER_H__
#define GL_SHADER_H__

#include <map>
#include <string>
#include <glad/glad.h>

using std::map;
using std::string;

class GLShader {
public:
    explicit GLShader();
    ~GLShader();

    void free();

    bool hasShader(GLuint type);
    bool load(GLuint type, const string & shaderFile);
    bool link();
    void use(bool used = true);
    
    GLint location(const char* uniform);

    inline void set1f(const GLchar* name, GLfloat v0) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1f(loc, v0);
    }
    inline void set2f(const GLchar* name, GLfloat v0, GLfloat v1) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2f(loc, v0, v1);
    }
    inline void set3f(const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3f(loc, v0, v1, v2);
    }
    inline void set4f(const GLchar* name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4f(loc, v0, v1, v2, v3);
    }

    inline void set1i(const GLchar* name, GLint v0) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1i(loc, v0);
    }
    inline void set2i(const GLchar* name, GLint v0, GLint v1) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2i(loc, v0, v1);
    }
    inline void set3i(const GLchar* name, GLint v0, GLint v1, GLint v2) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3i(loc, v0, v1, v2);
    }
    inline void set4i(const GLchar* name, GLint v0, GLint v1, GLint v2, GLint v3) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4i(loc, v0, v1, v2, v3);
    }

    inline void set1ui(const GLchar* name, GLuint v0) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1ui(loc, v0);
    }
    inline void set2ui(const GLchar* name, GLuint v0, GLuint v1) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2ui(loc, v0, v1);
    }
    inline void set3ui(const GLchar* name, GLuint v0, GLuint v1, GLuint v2) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3ui(loc, v0, v1, v2);
    }
    inline void set4ui(const GLchar* name, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4ui(loc, v0, v1, v2, v3);
    }

    inline void set1fv(const GLchar* name, GLsizei count, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1fv(loc, count, value);
    }
    inline void set2fv(const GLchar* name, GLsizei count, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2fv(loc, count, value);
    }
    inline void set3fv(const GLchar* name, GLsizei count, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3fv(loc, count, value);
    }
    inline void set4fv(const GLchar* name, GLsizei count, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4fv(loc, count, value);
    }
    
    inline void set1iv(const GLchar* name, GLsizei count, const GLint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1iv(loc, count, value);
    }
    inline void set2iv(const GLchar* name, GLsizei count, const GLint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2iv(loc, count, value);
    }
    inline void set3iv(const GLchar* name, GLsizei count, const GLint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3iv(loc, count, value);
    }
    inline void set4iv(const GLchar* name, GLsizei count, const GLint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4iv(loc, count, value);
    }

    inline void set1uiv(const GLchar* name, GLsizei count, const GLuint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform1uiv(loc, count, value);
    }
    inline void set2uiv(const GLchar* name, GLsizei count, const GLuint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform2uiv(loc, count, value);
    }
    inline void set3uiv(const GLchar* name, GLsizei count, const GLuint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform3uiv(loc, count, value);
    }
    inline void set4uiv(const GLchar* name, GLsizei count, const GLuint *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniform4uiv(loc, count, value);
    }

    inline void setMat2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix2fv(loc, count, transpose, value);
    }
    inline void setMat3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix3fv(loc, count, transpose, value);
    }
    inline void setMat4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix4fv(loc, count, transpose, value);
    }

    inline void setMat2x3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix2x3fv(loc, count, transpose, value);
    }
    inline void setMat3x2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix3x2fv(loc, count, transpose, value);
    }
    inline void setMat2x4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix2x4fv(loc, count, transpose, value);
    }
    inline void setMat4x2fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix4x2fv(loc, count, transpose, value);
    }
    inline void setMat3x4fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix3x4fv(loc, count, transpose, value);
    }
    inline void setMat4x3fv(const GLchar* name, GLsizei count, GLboolean transpose, const GLfloat *value) {
        GLint loc = location(name);
        if( loc >= 0 ) 
            glUniformMatrix4x3fv(loc, count, transpose, value);
    }

public:
    GLuint id;

protected:

private:
    map<const string, GLint> mUniformsLoc;
    map<GLuint, GLuint> mLoadedShaders;
};


#endif
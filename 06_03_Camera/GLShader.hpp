#ifndef GLSHADER_H__
#define GLSHADER_H__

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class GLShader {
public:
    bool loadShader(GLuint type, const string& shaderSource);
    bool loadShaderFile(GLuint type, const string& file);
    bool compile();
    bool createProgram();
    bool attach();
    void detach();
    bool link();
    bool use(bool use_it = true);
    void freeShader();
    void freeProgram();
    GLuint program() const;

    inline GLint uniformLocation(const GLchar* name) {
        return glGetUniformLocation(m_shaderProgram, name);
    }

    inline void setUniform1f(GLint loc, GLfloat v0){
        if( m_used || use() )
            glUniform1f(loc, v0);
    }

    inline void setUniform2f(GLint loc, GLfloat v0, GLfloat v1) {
        if( m_used || use() )
            glUniform2f(loc, v0, v1);
    }

    inline void setUniform3f(GLint loc, GLfloat v0, GLfloat v1, GLfloat v2) {
        if( m_used || use() )
            glUniform3f(loc, v0, v1, v2);
    }

    inline void setUniform4f(GLint loc, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
        if( m_used || use() )
            glUniform4f(loc, v0, v1, v2, v3);
    }

    inline void setUniform1i(GLint loc, GLint v0) {
        if( m_used || use() )
            glUniform1i(loc, v0);
    }

    inline void setUniform2i(GLint loc, GLint v0, GLint v1) {
        if( m_used || use() )
            glUniform2i(loc, v0, v1);
    }

    inline void setUniform3i(GLint loc, GLint v0, GLint v1, GLint v2) {
        if( m_used || use() )
            glUniform3i(loc, v0, v1, v2);
    }

    inline void setUniform4i(GLint loc, GLint v0, GLint v1, GLint v2, GLint v3) {
        if( m_used || use() )
            glUniform4i(loc, v0, v1, v2, v3);
    }

    inline void setUniform1ui(GLint loc, GLuint v0) {
        if( m_used || use() )
            glUniform1ui(loc, v0);
    }

    inline void setUniform2ui(GLint loc, GLuint v0, GLuint v1) {
        if( m_used || use() )
            glUniform2ui(loc, v0, v1);
    }

    inline void setUniform3ui(GLint loc, GLuint v0, GLuint v1, GLuint v2) {
        if( m_used || use() )
            glUniform3ui(loc, v0, v1, v2);
    }

    inline void setUniform4ui(GLint loc, GLuint v0, GLuint v1, GLuint v2, GLuint v3) {
        if( m_used || use() )
            glUniform4ui(loc, v0, v1, v2, v3);
    }

    inline void setUniform1fv(GLint loc, GLsizei count, const GLfloat *value){
        if( m_used || use() )
            glUniform1fv(loc, count, value);
    }

    inline void setUniform2fv(GLint loc, GLsizei count, const GLfloat *value) {
        if( m_used || use() )
            glUniform2fv(loc, count, value);
    }

    inline void setUniform3fv(GLint loc, GLsizei count, const GLfloat *value) {
        if( m_used || use() )
            glUniform3fv(loc, count, value);
    }

    inline void setUniform4fv(GLint loc, GLsizei count, const GLfloat *value) {
        if( m_used || use() )
            glUniform4fv(loc, count, value);
    }

    inline void setUniform1iv(GLint loc, GLsizei count, const GLint *value) {
        if( m_used || use() )
            glUniform1iv(loc, count, value);
    }

    inline void setUniform2iv(GLint loc, GLsizei count, const GLint *value) {
        if( m_used || use() )
            glUniform2iv(loc, count, value);
    }

    inline void setUniform3iv(GLint loc, GLsizei count, const GLint *value) {
        if( m_used || use() )
            glUniform3iv(loc, count, value);
    }

    inline void setUniform4iv(GLint loc, GLsizei count, const GLint *value) {
        if( m_used || use() )
            glUniform4iv(loc, count, value);
    }

    inline void setUniform1uiv(GLint loc, GLsizei count, const GLuint *value) {
        if( m_used || use() )
            glUniform1uiv(loc, count, value);
    }

    inline void setUniform2uiv(GLint loc, GLsizei count, const GLuint *value) {
        if( m_used || use() )
            glUniform2uiv(loc, count, value);
    }

    inline void setUniform3uiv(GLint loc, GLsizei count, const GLuint *value) {
        if( m_used || use() )
            glUniform3uiv(loc, count, value);
    }

    inline void setUniform4uiv(GLint loc, GLsizei count, const GLuint *value) {
        if( m_used || use() )
            glUniform4uiv(loc, count, value);
    }

    inline void setUniformMatrix2fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix2fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix3fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix3fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix4fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix4fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix2x3fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix2x3fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix3x2fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix3x2fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix2x4fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix2x4fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix4x2fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix4x2fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix3x4fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix3x4fv(loc, count, transpose ,value);
    }

    inline void setUniformMatrix4x3fv(GLint loc, GLsizei count, GLboolean transpose, const GLfloat *value) {
        if( m_used || use() )
            glUniformMatrix4x3fv(loc, count, transpose ,value);
    }

    GLShader();
    ~GLShader();

private:
    bool m_linked;
    bool m_compiled_vshader;
    bool m_compiled_fshader;
    bool m_attached_vshader;
    bool m_attached_fshader;
    bool m_used;
    GLuint m_vertShader;
    GLuint m_fragShader;
    GLuint m_shaderProgram;
    vector<string> m_vertShaders;
    vector<string> m_fragShaders;
};

#endif  // GLSHADER_H__

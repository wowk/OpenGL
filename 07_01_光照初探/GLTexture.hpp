#ifndef GL_TEXTURE_H__
#define GL_TEXTURE_H__

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

using std::cout;
using std::endl;

class GLTexture {
public:
    explicit GLTexture(GLuint target = 0);
    ~GLTexture();
    void setTarget(GLuint target);
    bool create();
    bool bind();
    void unbind();
    bool genMipmap();
    bool loadImage(const char* imgName);

    inline void setTexParameterf(GLenum pname, GLfloat param) {
        if( m_texture && m_bind ){
            glTexParameterf(m_target, pname, param);
        }else{
            cout << "1-cant bind texture" << endl;
        }
    }

    inline void setTexParameteri(GLenum pname, GLint param) {
        if( m_texture && m_bind ){
            glTexParameteri(m_target, pname, param);
        }else{
            cout << "2-cant bind texture" << endl;
        }
    }

    inline void setTexParameterfv(GLenum pname, const GLfloat * params) {
        if( m_texture && m_bind ){
            glTexParameterfv(m_target, pname, params);
        }else{
            cout << "3-cant bind texture" << endl;
        }
    }

    inline void setTexParameteriv(GLenum pname, const GLint * params) {
        if( m_texture && m_bind ){
            glTexParameteriv(m_target, pname, params);
        }else{
            cout << "4-cant bind texture" << endl;
        }
    }

    inline void setTexParameterIiv(GLenum pname, const GLint * params) {
        if( m_texture && m_bind ){
            glTexParameterIiv(m_target, pname, params);
        }else{
            cout << "5-cant bind texture" << endl;
        }
    }

    inline void setTexParameterIuiv(GLenum pname, const GLuint * params) {
        if( m_texture && m_bind ){
            glTexParameterIuiv(m_target, pname, params);
        }else{
            cout << "6-cant bind texture" << endl;
        }
    }

private:
    bool m_bind;
    GLuint m_texture;
    GLuint m_target;
};

#endif//GLTEXTURE_H__

#include <GLTexture.hpp>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


using std::cout;
using std::endl;

// GLTexture::GLTexture(GLuint target, GLuint texture)
// {
//     mTarget     = target;
//     mTexture    = texture;
// }
GLTexture::GLTexture(){}

GLTexture::GLTexture(GLuint target)
{
    create(target);
}

bool GLTexture::create(GLuint target)
{
    mTarget = target;
    glGenTextures(1, &mTexture);
    if( mTexture == 0 ){
        cout << "create texture failed" << endl;
    }
}

GLTexture::~GLTexture()
{
    free();
}

void GLTexture::free()
{
    if( mTexture > 0 ){
        glDeleteTextures(1, &mTexture);
    }
}

void GLTexture::setFilter(GLuint magFilter, GLuint minFilter)
{
    glTexParameteri(mTarget, GL_TEXTURE_MAG_FILTER, magFilter);
    glTexParameteri(mTarget, GL_TEXTURE_MIN_FILTER, minFilter);
}

void GLTexture::setWrapType(GLuint s, GLuint t, GLuint r)
{
    glTexParameteri(mTarget, GL_TEXTURE_WRAP_S, s);
    glTexParameteri(mTarget, GL_TEXTURE_WRAP_T, t);
    glTexParameteri(mTarget, GL_TEXTURE_WRAP_R, r);
}

void GLTexture::use(bool used)
{
    if( used ){
        glBindTexture(mTarget, mTexture);
    }else{
        glBindTexture(mTarget, 0);
    }
}

void GLTexture::generateMipmap()
{
    glGenerateMipmap(mTarget);
}

bool GLTexture::loadImage2D(const string & img, GLint level)
{
    SDL_Surface* image = IMG_Load(img.c_str());
    if( !image ){
        return false;
    }

    GLuint format;

    switch ( image->format->BytesPerPixel ){
        case 1:
            format = GL_RED;
            break;
        case 3:
            format = GL_RGB;
            break;
        case 4:
            format = GL_RGBA;
            break;
        default:
            cout << "Image format Not supported" << endl;
            SDL_FreeSurface(image);
            return false;
    }

    glTexImage2D(mTarget, level, format, image->w, image->h, 0, 
                    format, GL_UNSIGNED_BYTE, image->pixels);

    SDL_FreeSurface(image);
    return true;
}
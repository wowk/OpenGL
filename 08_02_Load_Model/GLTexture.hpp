#ifndef GL_TEXTURE_H__
#define GL_TEXTURE_H__

#include <glad/glad.h>
#include <string>

using std::string;


class GLTexture {
public:
    // GLTexture(GLuint target, GLuint texture);
    GLTexture();
    GLTexture(GLuint target);
    bool create(GLuint target);
    ~GLTexture();
    void free();

    void setFilter(GLuint mag = GL_LINEAR, GLuint = GL_LINEAR);
    void setWrapType(GLuint s = GL_CLAMP_TO_EDGE, 
                    GLuint t = GL_CLAMP_TO_EDGE, 
                    GLuint r = GL_CLAMP_TO_EDGE);
    void use(bool used = true);
    void generateMipmap();
    bool loadImage2D(const string & img, GLint level = 0);

private:
    GLuint mTexture;
    GLuint mTarget;
};

#endif
#ifndef GL_MESH_H__
#define GL_MESH_H__

#include <vector>
#include <string>
#include <GLTexture.hpp>
#include <GLShader.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>


using std::vector;
using std::string;

struct Vertex {
    glm::vec3 pos;
    glm::vec3 normal;
    glm::vec2 coord;
};

class GLMesh {
public:
    GLMesh(vector<Vertex> v, vector<GLTexture*> t, vector<GLuint> i);
    void draw(GLShader& shader);
    void setup();
    ~GLMesh();

public:
    vector<Vertex> mVertices;
    vector<GLTexture*> mTextures;
    vector<GLuint> mIndices;
    GLuint vao;
    GLuint vbo;
    GLuint veo;
};

#endif//GL_MESH_H__

#include <GLMesh.hpp>
#include <cstddef>
#include <iostream>

using std::cout;
using std::endl;

void GLMesh::draw(GLShader &shader)
{
    for( unsigned int i = 0 ; i < mTextures.size() ; i ++ ){
        glActiveTexture(GL_TEXTURE0 + i);
        shader.set1i("textureSampler1", i);
        mTextures[i]->use();
    }
    glActiveTexture(GL_TEXTURE0);

    shader.use();
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    shader.use(false);
    for( unsigned int i = 0 ; i < mTextures.size() ; i ++ ){
        mTextures[i]->use(false);
    }
}

void GLMesh::setup()
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(),
                 mVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE,
                          sizeof(Vertex), (GLvoid*)offsetof(Vertex, coord));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &veo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, veo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mIndices.size(),
                 mIndices.data(), GL_STATIC_DRAW);

    glBindVertexArray(0);
}

GLMesh::~GLMesh()
{
    glDeleteBuffers(1, &veo);
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    for( auto ptr : mTextures ){
        delete ptr;
    }
    mTextures.clear();
    mVertices.clear();
    mIndices.clear();
}

GLMesh::GLMesh(vector<Vertex> v, vector<GLTexture*> t, vector<GLuint> i)
{
    mVertices   =   v;
    mTextures   =   t;
    mIndices    =   i;
    setup();
}

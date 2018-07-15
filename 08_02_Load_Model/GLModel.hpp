#ifndef GL_MODEL_H__
#define GL_MODEL_H__

#include <list>
#include <string>
#include <GLMesh.hpp>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>


using std::list;
using std::string;

class GLModel {
public:
    GLModel(const char* modelDir);
    GLModel(const string & s);
    ~GLModel();
    bool loadMesh(string s);
    void draw(GLShader & s);
    void processNode(aiNode* node, const aiScene* scene);
    GLMesh* processMesh(aiMesh* mesh, const aiScene* scene);
private:
    list<GLMesh*> meshes;
    string dir;
};

#endif//GL_MODEL_H__

#include <GLModel.hpp>
#include <Utils.hpp>
#include <iostream>

using std::cout;
using std::endl;

GLModel::GLModel(const char *modelDir)
{
    dir.append(modelDir);
}

GLModel::GLModel(const std::string &s)
{
    dir = s;
}

GLModel::~GLModel()
{
    for( auto ptr : meshes ){
        delete ptr;
    }
    meshes.clear();
}

bool GLModel::init()
{
    return false;
}

bool GLModel::loadMesh(std::string s)
{
    Assimp::Importer import;
    GLMesh* mesh;

    auto model = import.ReadFile((dir+"/"+s).c_str(), 0);
    if( !model ){
        cout << "Load Error" << endl;
        return false;
    }

    processNode(model->mRootNode, model);

    cout << "Mesh Count: " << meshes.size() << endl;

    return true;
}

void GLModel::draw(GLShader &s)
{
    for( auto mesh : meshes ){
        mesh->draw(s);
    }
}

bool GLModel::processNode(aiNode *node, const aiScene *scene)
{
    for( unsigned int i = 0 ; i < node->mNumMeshes ; i ++ ){
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        auto meshObj = processMesh(mesh, scene);
        meshes.push_back(meshObj);
    }

    for( unsigned int i = 0 ; i < node->mNumChildren ; i ++ ){
        processNode(node->mChildren[i], scene);
    }

    return true;
}

GLMesh* GLModel::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex> vertices;
    vector<GLTexture*> textures;
    vector<GLuint> indices;

    if( mesh->HasPositions() ){
        for( unsigned i = 0 ; i < mesh->mNumVertices ; i ++ ){
            Vertex v;
            auto & vertex = mesh->mVertices[i];
            v.pos.x = vertex.x;
            v.pos.y = vertex.y;
            v.pos.z = vertex.z;

            if( mesh->HasTextureCoords(0) ){
                auto & coord = mesh->mTextureCoords[0][i];
                v.coord.x   = coord.x;
                v.coord.y   = coord.y;
            }

            if( mesh->HasNormals() ){
                auto & normal = mesh->mNormals[i];
                v.normal.x  = normal.x;
                v.normal.y  = normal.y;
                v.normal.z  = normal.z;
            }
            vertices.push_back(v);
        }
    }

    if( mesh->HasFaces() ){
        for( unsigned i = 0 ; i < mesh->mNumFaces ; i ++ ){
            auto face = mesh->mFaces[i];
            if( face.mNumIndices == 4 ){
                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[2]);
                indices.push_back(face.mIndices[3]);
            }else{
                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
            }
        }
    }

    auto material = scene->mMaterials[mesh->mMaterialIndex];
    if( material ){
        string path = dir + "/";
        aiString subPath;

        material->GetTexture(aiTextureType_DIFFUSE, 0, &subPath);
        path.append(subPath.C_Str());
        if( Utils::FileUtils::isExist(path) ){
            auto texture = new GLTexture(GL_TEXTURE_2D);
            texture->use();
            texture->setFilter();
            texture->setWrapType();
            if( !texture->loadImage2D(path.c_str()) ){
                cout << "Load Image " << path << " failed" << endl;
            }
            texture->generateMipmap();
            texture->use(false);
            textures.push_back(texture);
        }
    }
    // cout << "vertices: " << vertices.size() 
    //      << ", indices:  " << indices.size()
    //      << ", textures: " << textures.size() << endl;
    return new GLMesh(vertices, textures, indices);
}

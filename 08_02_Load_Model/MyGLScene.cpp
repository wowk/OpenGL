#include <MyGLScene.hpp>
#include <GLApplication.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <cmath>
#include <assimp/Importer.hpp>
#include <assimp/IOStream.hpp>
#include <assimp/scene.h>


using std::cout;
using std::cerr;
using std::endl;


bool MyGLScene::init()
{
    keyMap[SDLK_w] = false;
    keyMap[SDLK_a] = false;
    keyMap[SDLK_s] = false;
    keyMap[SDLK_d] = false;

    onKeyDownEvent = [=](const SDL_KeyboardEvent* event){
        keyMap[event->keysym.sym] = true;
    };

    onKeyUpEvent = [=](const SDL_KeyboardEvent* event){
        keyMap[event->keysym.sym] = false;
    };

    onMouseWheelEvent = [=](const SDL_MouseWheelEvent* event){
    };

    onMouseMotionEvent = [=](const SDL_MouseMotionEvent* event){
        GLfloat mouseSensitivity = 0.05f;
        camera.moveDirection(event->xrel * mouseSensitivity, - event->yrel * mouseSensitivity);
    };

    if( !shader.load(GL_VERTEX_SHADER, "../resources/shaders/model.vert") ){
        cout << "failed to load shader model.vert" << endl;
    }
    if( !shader.load(GL_FRAGMENT_SHADER, "../resources/shaders/model.frag") ){
        cout << "failed to load shader model.frag" << endl;
    }
    shader.link();
    
    model = new GLModel("../resources/models/City");
    model->loadMesh("City.obj");
    

    return true;
}

void MyGLScene::update(GLfloat delta)
{
    GLfloat cameraSpeed = 0.3f;
    if( keyMap[SDLK_w] ){
        camera.moveEye(0.0, cameraSpeed * delta);
    }
    if( keyMap[SDLK_s] ){
        camera.moveEye(0.0, -cameraSpeed * delta);
    }
    if( keyMap[SDLK_a] ){
        camera.moveEye(-cameraSpeed * delta, 0.0);
    }
    if( keyMap[SDLK_d] ){
        camera.moveEye(cameraSpeed * delta, 0.0);
    }
    if( keyMap[SDLK_ESCAPE] ){
        GLApplication::inst()->close();
    }
    if( keyMap[SDLK_l] ){
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    if( keyMap[SDLK_k] ){
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    camera.update(delta);
}

void MyGLScene::draw()
{
    glm::mat4 modelMatrix(1.0f);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.0f));
    shader.use();
    shader.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(modelMatrix));
    shader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
    shader.setMat4fv("proj", 1, GL_FALSE, glm::value_ptr(camera.projectionMatrix()));
    shader.use(false);
    model->draw(shader);
}

MyGLScene::~MyGLScene()
{
    shader.free();
}

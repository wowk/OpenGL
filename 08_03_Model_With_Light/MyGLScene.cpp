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

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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

    onMouseButtonDownEvent = [=](const SDL_MouseButtonEvent* event){
        if( event->button == 2 ){
            female->setScale(glm::vec3(2.0f, 2.0f, 2.0f));
            cout << "scale up" << endl;
        }else if( event->button == 1 ){
            female->setScale(glm::vec3(0.5f, 0.5f, 0.5f));
            cout << "scale down" << endl;
        }
    };

    glm::vec3 lightColor(1.0, 1.0, 1.0);
    glm::vec3 lightDir(-1.0f, 1.0f, 1.0f);
    glm::vec3 lightPos(-200.0f, 200.0f, 200.0f);

    if( !sunShader.load(GL_VERTEX_SHADER, "resources/shaders/globalLight.vert") ){
        cout << "failed to load shader sun.vert" << endl;
    }
    if( !sunShader.load(GL_FRAGMENT_SHADER, "resources/shaders/globalLight.frag") ){
        cout << "failed to load shader sun.frag" << endl;
    }
    sunShader.link();
    sunShader.use();
    sunShader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
    sunShader.setMat4fv("proj", 1, GL_FALSE, glm::value_ptr(camera.projectionMatrix()));
    sunShader.set3fv("Color", 1, glm::value_ptr(lightColor));
    sunShader.use(false);

    sun = new GLModel("resources/models/sphere");
    if( !sun->loadMesh("sphere.obj") ){
        cout << "Load sphere.obj failed" << endl;
    }
    sun->setPosition(lightPos);
    sun->setScale(glm::vec3(20, 20, 20));

    glm::vec3 materialAmbient(0.5, 0.5, 0.5);
    glm::vec3 materialDiffuse(0.4, 0.4, 0.4);
    glm::vec3 materialSpecular(0.3, 0.3, 0.3);
    int materialSpecStrength = 64;


    if( !modelShader.load(GL_VERTEX_SHADER, "resources/shaders/model.vert") ){
        cout << "failed to load shader model.vert" << endl;
    }
    if( !modelShader.load(GL_FRAGMENT_SHADER, "resources/shaders/model.frag") ){
        cout << "failed to load shader model.frag" << endl;
    }
    modelShader.link();
    modelShader.use();
    modelShader.setMat4fv("proj", 1, GL_FALSE, glm::value_ptr(camera.projectionMatrix()));
    modelShader.set3fv("light.color", 1, glm::value_ptr(lightColor));
    modelShader.set3fv("light.dir", 1, glm::value_ptr(lightDir));
    modelShader.set3fv("light.pos", 1, glm::value_ptr(lightPos));
    modelShader.set3fv("material.ambient", 1, glm::value_ptr(materialAmbient));
    modelShader.set3fv("material.diffuse", 1, glm::value_ptr(materialDiffuse));
    modelShader.set3fv("material.specular", 1, glm::value_ptr(materialSpecular));
    modelShader.set1i("material.specStrength", materialSpecStrength);
    modelShader.use(false);
    //model = new GLModel("resources/models/knight/");
    //if( !model->loadMesh("knight.obj") ){
    model = new GLModel("resources/models/City/");
    if( !model->loadMesh("City.obj") ){
        cout << "Load City.obj failed" << endl;
    }
    model->setPosition(glm::vec3(0.0f));
    //model->setScale(glm::vec3(10.0, 10.0, 10.0));

    female = new GLModel("resources/models/female/");
    if( !female->loadMesh("female02.obj") ){
        cout << "Load female02.obj failed" << endl;
    }
    female->setPosition(glm::vec3(0.0, 0.0, 0.0));
    female->setScale(glm::vec3(0.1f, 0.1f, 0.1f));

    //glDepthFunc(GL_EQUAL);
    for( unsigned i = 0 ; i < sizeof(glass)/sizeof(glass[0]) ; i ++ ){
        glass[i].init();
        glass[i].setPosition(glm::vec3(5.0f, 50.0f, i * 50.0f));
        glass[i].setScale(glm::vec3(50.0f, 50.0f, 50.0f));
    }

    return true;
}

void MyGLScene::update(GLfloat delta)
{
    GLfloat xOffset = 0.0f, yOffset = 0.0f;
    GLfloat cameraSpeed = 0.03f;

    if( keyMap[SDLK_w] ){
        yOffset += cameraSpeed * delta;
    }
    if( keyMap[SDLK_s] ){
        yOffset += -cameraSpeed * delta;
    }
    if( keyMap[SDLK_a] ){
        xOffset += -cameraSpeed * delta;
    }
    if( keyMap[SDLK_d] ){
        xOffset += cameraSpeed * delta;
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

    if( xOffset || yOffset ){
        camera.moveEye(xOffset, yOffset);
    }
    camera.update(delta);
}

void MyGLScene::draw()
{
    modelShader.use();
    modelShader.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(female->model()));
    modelShader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
    modelShader.use(false);
    female->draw(modelShader);

    sunShader.use();
    sunShader.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(sun->model()));
    sunShader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
    sunShader.use(false);
    sun->draw(sunShader);

    modelShader.use();
    modelShader.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(model->model()));
    modelShader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
    modelShader.set3fv("viewPos", 1, glm::value_ptr(camera.position()));
    modelShader.use(false);
    model->draw(modelShader);

    for( unsigned i = 0 ; i < sizeof(glass)/sizeof(glass[0]) ; i ++ ){
        modelShader.use();
        modelShader.setMat4fv("model", 1, GL_FALSE, glm::value_ptr(glass[i].model()));
        modelShader.setMat4fv("view", 1, GL_FALSE, glm::value_ptr(camera.viewMatrix()));
        modelShader.set3fv("viewPos", 1, glm::value_ptr(camera.position()));
        modelShader.use(false);
        glass[i].draw(modelShader);
    }
}

MyGLScene::~MyGLScene()
{
    sunShader.free();
    modelShader.free();
    delete sun;
    delete model;
}

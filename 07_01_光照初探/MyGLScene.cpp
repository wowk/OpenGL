#include <MyGLScene.hpp>
#include <GLApplication.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using std::cerr;
using std::endl;


bool MyGLScene::init()
{

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    onKeyDownEvent = [=](const SDL_KeyboardEvent* event){
        GLfloat cameraSpeed = 0.01f;
        switch (event->keysym.sym) {
        case SDLK_ESCAPE:
            GLApplication::inst()->setRunning(false);
            break;

        case SDLK_e:
            camera.moveEye(0.0f, cameraSpeed * 20);
            break;

        case SDLK_d:
            camera.moveEye(0.0f, -cameraSpeed * 20);
            break;

        case SDLK_s:
            camera.moveEye(-cameraSpeed, 0.0f);
            break;

        case SDLK_f:
            camera.moveEye(cameraSpeed, 0.0f);
            break;

        default:
            break;
        }
    };

    onMouseWheelEvent = [=](const SDL_MouseWheelEvent* event){
        camera.setAspect(camera.aspect() + static_cast<GLfloat>(event->y) / 30.0f);
    };

    onMouseMotionEvent = [=](const SDL_MouseMotionEvent* event){
        GLfloat mouseSensitivity = 0.05f;
        camera.moveDirection(event->xrel * mouseSensitivity, - event->yrel * mouseSensitivity);
    };

    camera.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
    camera.moveDirection(90.0f, 0.0f);

    shader.createProgram();
    shader.loadShaderFile(GL_VERTEX_SHADER, "shader.vert");
    shader.loadShaderFile(GL_FRAGMENT_SHADER, "shader.frag");
    shader.compile() && shader.attach() && shader.link();
    shader.detach();
    shader.freeShader();

    surfaceColorLoc = shader.uniformLocation("surfaceColor");
    tex1Location = shader.uniformLocation("texSampler1");
    projLoc = shader.uniformLocation("proj");
    viewLoc = shader.uniformLocation("view");
    modelLoc = shader.uniformLocation("model");

    texture.setTarget(GL_TEXTURE_2D);
    texture.create();
    texture.bind();
    texture.setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    texture.setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    texture.setTexParameteri(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    texture.setTexParameteri(GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    texture.setTexParameteri(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture.loadImage("texture2.png");
    texture.genMipmap();
    texture.unbind();

    return true;
}

void MyGLScene::update(GLfloat delta)
{
    camera.update(delta);
}

void MyGLScene::draw()
{
    cube.bind();
    glActiveTexture(GL_TEXTURE0);
    texture.bind();
    shader.use();
    shader.setUniform1i(tex1Location, 0);
    shader.setUniformMatrix4fv(viewLoc, 1, false, glm::value_ptr(camera.viewMatrix()));
    shader.setUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(camera.projectionMatrix()));

    glm::vec3 cube1Color(0.1f, 0.01f, 0.001f);
    glm::vec3 cube2Color(1.0f, 1.0f, 1.0f);
    glm::mat4 model;
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 4.0f));
    shader.setUniform3fv(surfaceColorLoc, 1, glm::value_ptr(cube1Color));
    shader.setUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    cube.draw();

    model = glm::translate(model, glm::vec3(0.0f, 2.0f, 0.0f));
    shader.setUniform3fv(surfaceColorLoc, 1, glm::value_ptr(cube2Color));
    shader.setUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    cube.draw();

    texture.unbind();
    shader.use(false);
    glBindVertexArray(0);
}

MyGLScene::~MyGLScene()
{
    texture.unbind();
    shader.use(false);
    shader.freeShader();
    shader.freeProgram();
}

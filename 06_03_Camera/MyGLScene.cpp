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
    onKeyDownEvent = [=](const SDL_KeyboardEvent* event){
        GLfloat cameraSpeed = 0.01f;
        switch (event->keysym.sym) {
        case SDLK_ESCAPE:
            GLApplication::inst()->setRunning(false);
            break;

        case SDLK_e:
            camera.moveEye(0.0f, cameraSpeed);
            break;

        case SDLK_s:
            camera.moveEye(-cameraSpeed, 0.0f);
            break;

        case SDLK_f:
            camera.moveEye(cameraSpeed, 0.0f);
            break;

        case SDLK_d:
            camera.moveEye(0.0f, -cameraSpeed);
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
    camera.setFront(glm::vec3(0.0f, 0.0f, -1.0f));

    glGenVertexArrays(2, vao);
    glGenBuffers(2, vbo);


    GLfloat vertices[] = {
        0.5f,   0.5f,   0.0f,   1.0f,   1.0f,
        0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,
        -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,
    };
    glBindVertexArray(vao[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    GLfloat vertices2[] = {
        100.f,  -20.5f,  100.f,  1.0f,   1.0f,
        100.f,  -20.5f,  -100.f, 1.0f,   0.0f,
        -100.f, -20.5f,  100.f,  0.0f,   1.0f,
        -100.f, -20.5f,  -100.f, 0.0f,   0.0f,
    };
    glBindVertexArray(vao[1]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)NULL);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);


    shader.createProgram();
    shader.loadShaderFile(GL_VERTEX_SHADER, "shader.vert");
    shader.loadShaderFile(GL_FRAGMENT_SHADER, "shader.frag");
    shader.compile() && shader.attach() && shader.link();
    shader.detach();
    shader.freeShader();

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
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    shader.setUniform1i(tex1Location, 0);

    shader.setUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(camera.modelMatrix()));
    shader.setUniformMatrix4fv(viewLoc, 1, false, glm::value_ptr(camera.viewMatrix()));
    shader.setUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(camera.projectionMatrix()));
    texture.bind();

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

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
    glDeleteBuffers(2, vbo);
    glDeleteVertexArrays(2, vao);
}

#include <MyGLScene.h>
#include <GLApplication.h>
#include <iostream>
#include <glm/matrix.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
using std::cerr;
using std::endl;


bool MyGLScene::init()
{
    onKeyDownEvent = [=](const SDL_KeyboardEvent* event){
        switch (event->keysym.sym) {
        case SDLK_ESCAPE:
            GLApplication::inst()->setRunning(false);
            break;

        case SDLK_UP:
            rotate += 0.01f;
            viewCamera.z += 0.05f;
            break;

        case SDLK_DOWN:
            rotate -= 0.01f;
            viewCamera.z -= 0.05f;
            break;

        case SDLK_LEFT:
            viewCamera.x += 0.05f;
            break;

        case SDLK_RIGHT:
            viewCamera.x -= 0.05f;
            break;

        default:
            break;
        }
    };

    onMouseWheelEvent = [=](const SDL_MouseWheelEvent* event){
        viewCamera.z += event->y;
    };

    onMouseMotionEvent = [=](const SDL_MouseMotionEvent* event){
        viewCamera.x -= event->xrel / 200.0f;
        viewCamera.y += event->yrel / 200.0f;
    };

    rotate = 0.0f;
    viewCamera = glm::vec3(0.0f, 0.0f, 0.0f);
    posCamera = glm::vec3(0.0f, 0.0f, 0.0f);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {
        0.5f,   0.5f,   0.0f,   1.0f,   1.0f,
        0.5f,   -0.5f,  0.0f,   1.0f,   0.0f,
        -0.5f,  0.5f,   0.0f,   0.0f,   1.0f,
        -0.5f,  -0.5f,  0.0f,   0.0f,   0.0f,
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
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
    texture.setTexParameteri(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    texture.setTexParameteri(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
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

}

void MyGLScene::draw()
{
    glm::mat4 model;
    model = glm::rotate(model, 0.0f, glm::vec3(1.0f, 0.0f, 0.0f));

    glm::mat4 view;
    view = glm::translate(view, glm::vec3(viewCamera.x, viewCamera.y, viewCamera.z));
    std::cout << viewCamera.x << ", " << viewCamera.y << ", " << viewCamera.z << std::endl;

    glm::mat4 proj;
    proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    glBindVertexArray(vao);
    shader.use();
    glActiveTexture(GL_TEXTURE0);
    shader.setUniform1i(tex1Location, 0);
    shader.setUniformMatrix4fv(modelLoc, 1, false, glm::value_ptr(model));
    shader.setUniformMatrix4fv(viewLoc, 1, false, glm::value_ptr(view));
    shader.setUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(proj));
    texture.bind();

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
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
}

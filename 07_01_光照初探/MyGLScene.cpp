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
        m_keymap[event->keysym.sym] = true;
        if( event->keysym.sym == SDLK_w ){
            m_keymap[SDLK_s] = false;
        }else if( event->keysym.sym == SDLK_s ){
            m_keymap[SDLK_w] = false;
        }else if( event->keysym.sym == SDLK_a ){
            m_keymap[SDLK_d] = false;
        }else if( event->keysym.sym == SDLK_d ){
            m_keymap[SDLK_a] = false;
        }
    };

    onKeyUpEvent = [=](const SDL_KeyboardEvent* event){
        m_keymap[event->keysym.sym] = false;
    };

    onMouseMotionEvent = [=](const SDL_MouseMotionEvent* event){
        GLfloat mouseSensitivity = 0.05f;
        camera.moveDirection(event->xrel * mouseSensitivity, - event->yrel * mouseSensitivity);
    };

    onMouseButtonDownEvent = [=](const SDL_MouseButtonEvent* event){
        if( event->button == 0 ){
            std::cout << "vblank_mode=0\n";
            SDL_GL_SetSwapInterval(1);
        }else{
            std::cout << "vblank_mode=1\n";
            SDL_GL_SetSwapInterval(0);
        }
    };

    onMouseWheelEvent = [=](const SDL_MouseWheelEvent* event){
        ambientStrength += event->y / 100.0f;
    };

    //环境光强度，乘以物体的颜色
    ambientStrength = 0.1f;

    m_keymap[SDLK_w] = false;
    m_keymap[SDLK_s] = false;
    m_keymap[SDLK_d] = false;
    m_keymap[SDLK_a] = false;
    m_keymap[SDLK_ESCAPE] = false;

    camera.setPosition(glm::vec3(0.0f, 0.0f, 1.0f));
    camera.setWorldUp(glm::vec3(0.0f, 1.0f, 0.0f));
    camera.moveDirection(90.0f, 0.0f);

    //光源使用自己的 shader
    shaderLight.createProgram();
    shaderLight.loadShaderFile(GL_VERTEX_SHADER, "Res/shader/light.vert");
    shaderLight.loadShaderFile(GL_FRAGMENT_SHADER, "Res/shader/light.frag");
    shaderLight.compile() && shaderLight.attach() && shaderLight.link();
    shaderLight.detach();
    shaderLight.freeShader();

    //方块使用自己的 shader
    shaderCube.createProgram();
    shaderCube.loadShaderFile(GL_VERTEX_SHADER, "Res/shader/cube.vert");
    shaderCube.loadShaderFile(GL_FRAGMENT_SHADER, "Res/shader/cube.frag");
    shaderCube.compile() && shaderCube.attach() && shaderCube.link();
    shaderCube.detach();
    shaderCube.freeShader();

    return true;
}

void MyGLScene::update(GLfloat delta)
{
    camera.update(delta);

    if( m_keymap[SDLK_ESCAPE] == true ){
        GLApplication::inst()->setRunning(false);
    }

    GLfloat cameraSpeed = 0.002f;
    if( m_keymap[SDLK_w] == true ){
        camera.moveEye(0.0f, cameraSpeed * delta);
    }else if( m_keymap[SDLK_s] == true ){
        camera.moveEye(0.0f, -cameraSpeed * delta);
    }

    if( m_keymap[SDLK_a] == true ){
        camera.moveEye(-cameraSpeed * delta, 0.0f);
    }else if( m_keymap[SDLK_d] == true ){
        camera.moveEye(cameraSpeed * delta, 0.0f);
    }
}

void MyGLScene::draw()
{

    GLint projLoc;
    GLint modelLoc;
    GLint viewLoc;
    GLint lightColorLoc;
    GLint cubeColorLoc;
    GLint lightPosLoc;
    GLint ambientStrengthLoc;


    lightColorLoc = shaderLight.uniformLocation("lightColor");
    projLoc = shaderLight.uniformLocation("proj");
    viewLoc = shaderLight.uniformLocation("view");
    modelLoc = shaderLight.uniformLocation("model");

    cube.bind();
    shaderLight.use();
    shaderLight.setUniformMatrix4fv(viewLoc, 1, false, glm::value_ptr(camera.viewMatrix()));
    shaderLight.setUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(camera.projectionMatrix()));


    /*
      设置光源的颜色，
      设置光源的位置
    */
    glm::vec3 lightPos = glm::vec3(-1.0f, 0.0f, 4.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::mat4 model;
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.1f));
    shaderLight.setUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
    shaderLight.setUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    cube.draw();

    /*
      告知方块儿的 shader 如下信息：
    1. 光源的位置
    2. 光源的颜色
    3. 方块的颜色
    4. 环境光的强度
    5. 方块的位置
    这样就能计算出 方块在光照和没有光照情况下的颜色了
    光源虽然是一个方块， 但是计算的时候是被当作一个 点 来看待的。
    方块每个像素的颜色是通过发现和光源的角度计算出来的，
    光源和像素的距离暂时没有参与到运算中， 这就意味这不管远近，
    只要光源和像素法线的角度相同， 光的强度就相同。
    */
    glm::vec3 cubeColor(1.f, 0.5f, 0.001f);
    projLoc = shaderCube.uniformLocation("proj");
    viewLoc = shaderCube.uniformLocation("view");
    modelLoc = shaderCube.uniformLocation("model");
    cubeColorLoc = shaderCube.uniformLocation("cubeColor");
    lightColorLoc = shaderCube.uniformLocation("lightColor");
    lightPosLoc = shaderCube.uniformLocation("lightPos");
    ambientStrengthLoc = shaderCube.uniformLocation("ambientStrength");

    glm::mat4 cubeModel;
    cubeModel = glm::translate(cubeModel, glm::vec3(1.0f, -1.5f, 0.0f));
    shaderCube.use();
    shaderCube.setUniform1f(ambientStrengthLoc, ambientStrength);
    shaderCube.setUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
    shaderCube.setUniform3fv(lightColorLoc, 1, glm::value_ptr(lightColor));
    shaderCube.setUniform3fv(cubeColorLoc, 1, glm::value_ptr(cubeColor));
    shaderCube.setUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
    shaderCube.setUniformMatrix4fv(viewLoc, 1, false, glm::value_ptr(camera.viewMatrix()));
    shaderCube.setUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(camera.projectionMatrix()));
    cube.draw();

    cube.draw();

    //cubeModel = glm::mat4(0.0f);
    cubeModel = glm::translate(cubeModel, glm::vec3(10.0f, 0.f, -2.0f));
    shaderCube.setUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));
    cube.draw();

    shaderCube.use(false);
    shaderLight.use(false);
    glBindVertexArray(0);
}

MyGLScene::~MyGLScene()
{
    texture.unbind();
    shaderCube.use(false);
    shaderCube.freeShader();
    shaderCube.freeProgram();
}

#include <MyGLApplication.hpp>
#include <MyGLScene.hpp>
#include <iostream>


MyGLApplication::MyGLApplication()
{

}

MyGLApplication::~MyGLApplication()
{
    while (currentScene()) {
        std::cout << "delete scene" << std::endl;
        delete currentScene();
        popScene();
    }
}

GLApplication *MyGLApplication::create()
{
    setInst(new MyGLApplication);
    return inst();
}

bool MyGLApplication::init(int argc, char* argv[])
{
    if( !GLApplication::init(argc, argv) ){
        inst()->close();
        return false;
    }

    auto scene = new MyGLScene();
    scene->init();

    runScene(scene);

    return true;
}

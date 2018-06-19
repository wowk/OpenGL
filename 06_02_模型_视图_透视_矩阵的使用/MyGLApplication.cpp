#include <MyGLApplication.h>
#include <MyGLScene.h>
#include <iostream>


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

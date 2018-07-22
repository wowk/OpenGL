#include <iostream>
#include <string>
#include <unistd.h>
#include <MyGLApplication.hpp>

using std::string;

int main(int argc, char *argv[])
{
    string path("../");
    path += basename(argv[0]);
    chdir(path.c_str());

    putenv("vblank_mode=1");
    auto app = MyGLApplication::create();

    app->init(argc, argv);
    app->mainloop();

    delete app;

    return 0;
}

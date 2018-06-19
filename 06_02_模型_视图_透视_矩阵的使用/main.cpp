#include <iostream>
#include <string>
#include <unistd.h>
#include <MyGLApplication.h>

using std::string;

int main(int argc, char *argv[])
{
    string dir = string("../") + string(basename(argv[0]));
    ::chdir(dir.c_str());

    auto app = MyGLApplication::create();

    app->init(argc, argv);
    app->mainloop();

    return 0;
}

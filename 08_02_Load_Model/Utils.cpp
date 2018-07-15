#include <Utils.hpp>
#include <fstream>

using std::ifstream;

bool Utils::FileUtils::loadFile(const string& fileName, string& s)
{
    ifstream fin;

    fin.open(fileName);
    if( !fin.is_open() ){
        return false;
    }

    char buf[512];
    while( fin.getline(buf, sizeof(buf)) ){
        s.append(buf);
        s.append("\n");
    }
    fin.close();

    return true;
}
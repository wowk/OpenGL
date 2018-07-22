#include <Utils.hpp>
#include <fstream>
#include <sys/stat.h>

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

bool Utils::FileUtils::isExist(const string& fileName)
{
    struct stat st;
    if( 0 > stat(fileName.c_str(), &st) || !S_ISREG(st.st_mode) ){
        return false;
    }
    return true;
}
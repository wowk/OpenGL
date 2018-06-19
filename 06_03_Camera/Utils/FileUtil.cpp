#include <Utils/FileUtil.h>
#include <fstream>
#include <iostream>


using std::cout;
using std::endl;
using std::ifstream;
using std::ios_base;


bool FileUtil::loadFile(const string &file, string &content)
{
    ifstream fin;

    fin.open(file);
    if( !fin.is_open() ){
        cout << "open file " << file << "failed" << endl;
        return false;
    }

    fin.seekg(0, ios_base::end);
    long fileSize = static_cast<long>(fin.tellg());
    fin.seekg(0, ios_base::beg);

    char* buffer = new char[fileSize + 1] {0};
    fin.read(buffer, fileSize);
    buffer[fileSize] = 0;
    fin.close();

    content = buffer;
    delete buffer;

    return true;
}

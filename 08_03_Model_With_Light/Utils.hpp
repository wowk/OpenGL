#ifndef UTILS_H__
#define UTILS_H__

#include <string>

using std::string;

namespace Utils {
    namespace FileUtils {
        bool loadFile(const string& fileName, string& s);
        bool isExist(const string& fileName);
    }
}

#endif
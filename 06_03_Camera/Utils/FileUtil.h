#ifndef FILE_UTILS_H__
#define FILE_UTILS_H__

#include <string>


using std::string;


namespace FileUtil {
    bool loadFile(const string & file, string & content);
}

#endif

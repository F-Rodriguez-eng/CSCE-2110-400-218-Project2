#ifndef FILEUTILS_H
#define FILEUTILS_H
#include "TextHandler.h"
#include <string>
#include <vector>
using namespace std;

namespace FileUtils {
    inline string trim(const string& str){
        return TextHandler::trimmer(str);
    }

    inline vector<string> split(const string& str, char delim){
        return TextHandler::split(str, delim);
    }

    inline string toLower(const string& str){
        return TextHandler::toLower(str);
    }

    inline string toUpper(const string& str){
        string out = str;
        for(size_t i =0; i < out.size(); ++i){
            if (out[i] >= 'a' && out[i] <= 'z'){
                out[i] = static_cast<char>(out[i] - 'a' + 'A');
            }
        }
        return out;
    }

}

#endif
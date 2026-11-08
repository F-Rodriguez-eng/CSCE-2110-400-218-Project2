//TextHandler.h (Text helper for trim, case, split)
//F. Rodriguez
#ifndef TEXTHANDLER_H
#define TEXTHANDLER_H
#include <cstddef>
#include <string>
#include <vector>
using namespace std;

namespace TextHandler {
    //Removes white spaces on ends, spaces in text stay (trimmer)
    inline string trimmer(const string& str) {
        const char* whiteSpace = " \t\n\f\r\v";
        size_t first = str.find_first_not_of(whiteSpace);
        if (first == string::npos){
            return "";
        }
        size_t last = str.find_last_not_of(whiteSpace);
        return str.substr(first, last - first + 1);
    }

    //makes copy of string in lower case (toLower)
    inline string toLower(const string& str) {
        string outPut = str;
        for (size_t i = 0; i < outPut.size(); ++i) {
            if (outPut[i] >= 'A' && outPut[i] <= 'Z') {
                outPut[i] = static_cast<char>(outPut[i] - 'A' + 'a');
            }
        }
        return outPut;
    }

    //splits str with delim, keeps empty fields
    inline vector<string> split(const)
}
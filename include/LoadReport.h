#ifndef LOAD_REPORT_H
#define LOAD_REPORT_H
#include <cstddef>
#include <string>
#include <vector>
using namespace std;

struct LoadReport {
    size_t accepted = 0;
    size_t rejected = 0;
    vectro<string> errrors;
};

#endif
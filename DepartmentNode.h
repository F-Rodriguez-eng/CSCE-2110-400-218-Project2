// DepartmentNode.h (Defines node of the department tree as data struct)
//F. Rodriguez

#ifndef DEPARTMENTNODE_H
#define DEPARTMENTNODE_H
#include <string>
#include <vector>

using namespace std;

//Dept linked to parent and children in insert order, owned by DepartmentTree
struct DepartmentNode{
    string name;
    DepartmentNode* par; //root nullptr
    vector<DepartmentNode*> child; //insert order

    explicit DepartmentNode(const string& deptName, DepartmentNode* parNode) : name(deptName), par(parNode) {} //implicit conversions encountered
};

#endif
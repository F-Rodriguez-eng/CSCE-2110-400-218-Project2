//DepartmentMenu.h (Handles tree options to avoid clutter in main.cpp)
//F. Rodriguez
#ifndef DEPARTMENTMENU_H
#define DEPARTMENTMENU_H
#include "DepartmentTree.h"

namespace DepartmentMenu{

    //adds department
    void addDept(DepartmentTree& tree);

    //searches dept
    void searchDept(const DepartmentTree& tree);

    //display of tree hierarchy
    void displayHier(const DepartmentTree& tree);

    //preorder traversal
    void preorder(const DepartmentTree& tree);

    //postorder traversal
    void postorder(const DepartmentTree& tree);

    //level order traversal
    void levelOrder(const DepartmentTree& tree);

    //Dept stats
    void statistics(const DepartmentTree& tree);

} //ns DepartmentMenu

#endif
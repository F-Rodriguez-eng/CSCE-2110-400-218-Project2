//DepartmentMenu.cpp (Main.cpp prompts and outputs)
//F. Rodriguez
#include "DepartmentMenu.h"
#include "TextHandler.h"
#include <iostream>
#include <string>
#include <vector>

namespace {
    //prompt with trim line return
    string promptUsr(const string& prompt){
        cout << prompt;
        string line;
        if(!getline(cin, line)){
            cin.clear();
            return "";
        }
        return TextHandler::trimmer(line);//trim.. of course
    }

    //print traversal chain
    void printTraversal(const string& heading, const vector<string>& names){
        cout << heading << ": \n";
        for(size_t i = 0; i < names.size(); ++i){
            if(i > 0){
                cout << " ==> ";
            }
            cout << names[i];
        }
        cout << "\n";
    }


} //ns

namespace DepartmentMenu{
    //prompts for name and parent UNLESS tree is empty, then no parent, add department
    void addDept(DepartmentTree& tree){
        string name = promptUsr("Enter new department name > ");
        if (name.empty()){
            cout << "ERROR: Department name cannot be blank.\n";
            return;
        }
        string err;
        if(tree.isEmpty()){
            if(tree.addDept(name, "", err)){
                cout << "Added '" << name << "' as root!\n";
            }
            else{
                cout << "ERROR: " << err << "\n";
            }
        return;
        }
        if(tree.findDept(name) != nullptr){
            cout << "ERROR: duplicate department name'" << name << "'.. No changes made to Tree.";
        }

        string parent = promptUsr("Enter name of parent department > ");
        if(parent.empty()){
            cout << "ERROR: Parent name can't be blank. No changes made to Tree.\n";
            return;
        }
        
        if (tree.addDept(name, parent, err)){
            const DepartmentNode* addedNode = tree.findDept(name);
            cout << "Added '" << addedNode->name << "' under '" << addedNode->par->name << "'\n";
        }
        else{
            cout << "ERROR: " << err << " No changes made to the Tree.\n";
        }
    }

    //name, parent except for root which is none, dir child count and depth
    void searchDept(const DepartmentTree& tree){
        string name = promptUsr("Enter department name > ");
        if(name.empty()){
            cout << "ERROR: Department name cannot be blank.\n";
            return;
        }
        if(tree.isEmpty()){
            cout << "Departments not loaded.\n";
            return;
        }

        const DepartmentNode* node = tree.findDept(name);
        if (node == nullptr){
            cout << "Department '" << name << "' not found. \n";
            return;
        }

        cout << "Department: " << node->name << endl;
        cout << "Parent: " << (node->par ? node->par->name : "None") << endl;
        cout << "Direct children: " << node->child.size() << endl;
        cout << "Depth: " << tree.depth(node) << endl;
    }

    //hierarchy with indents
    void displayHier(const DepartmentTree& tree){
        cout << "Department Hierachy:\n";
        tree.displayDeptHier(cout);
    }

    //Prints preorder sequence
    void preorder(const DepartmentTree& tree){
        if(tree.isEmpty()){
            cout << "Departments not loaded.\n";
            return;
        }

        printTraversal("Preorder traversal", tree.deptNamePre());
    }




}
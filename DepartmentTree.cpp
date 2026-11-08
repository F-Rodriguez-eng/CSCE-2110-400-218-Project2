//DepartmentTree.cpp (Impementing department tree ( load, add, search, trav, stats)
//F. Rodriguez
#include "DepartmentTree.h"
#include "TextHandler.h"
#include <fstream>
#include <iostream>
#include <queue>

namespace {
    const char* const RT_PAR = "NONE"; //no parent to root..

    //File name loaded in path
    string findFileName(const string& path) {
        size_t position = path.find_last_of("/\\");
        if (position == string::npos) {
            return path;
        }
        return path.substr(position + 1);
    }

    void rejectCatch(const string& file, size_t lineNumber, const string& reas, DeptFileLoadingResult& result){
        cout << "WAIT! Warning: " << file << " Line " << lineNumber << " rejected: " << reas << " [This record will be skipped]\n";//infile rejection msg
        ++result.rejected;
    }

    void summary(const string& file, const DeptFileLoadingResult& result){
        cout << file << " loaded: " << result.loaded << "accepted, " << result.rejected << " rejected.\n";
    }

} //ns

//class DepartmentTree implementation 

//Constructor, empty tree
DepartmentTree::DepartmentTree() : root(nullptr), count(0) {}

//Destructor, clears nodes
DepartmentTree::~DepartmentTree() {
    clear();
}

//deletes all nodes, tree will be empty
void DepartmentTree::clear() {
    delNode(root);
    root = nullptr;
    count = 0;
}

//Deletes node and descendants
void DepartmentTree::delNode(DepartmentNode* node) {
    if(node == nullptr){
        return;
    }
    for(size_t i = 0; i < node->child.size(); ++i){
        delNode(node->child[i]);
    }
    delete node;
}

bool DepartmentTree::isEmpty() const {
    return root == nullptr;
}

size_t DepartmentTree::size() const{
    return count;
}

//finds dept ingoring cases, preorder
DepartmentNode* DepartmentTree::searchNode(const string& name) const{
    if (root == nullptr){
        return nullptr;
    }
    string key = TextHandler::toLower(TextHandler::trimmer(name));
    vector<DepartmentNode*> stack;
    stack.push_back(root);
    while(!stack.empty()){//preorder search
        DepartmentNode* node = stack.back();
        stack.pop_back();
        if(TextHandler::toLower(node->name) == key){
            return node;                                //found!
        }
        for(size_t i = node->child.size(); i > 0; --i){
            stack.push_back(node->child[i - 1]);
        }
    }
    return nullptr;//not found
}

//read through lookup, if not found return null
const DepartmentNode* DepartmentTree::findDept(const string& name) const{
    return searchNode(name);
}

//adds dept starting from root
bool DepartmentTree::addDept(const string& name, const string& parentName, string& err){
    string deptName = TextHandler::trimmer(name);
    if (deptName.empty()){
        err = "Department name can't be empty!";
        return false;
    }
    if(searchNode(deptName)!=nullptr){
        err = "Duplicate department name found: '" + deptName + "'.";
        return false;
    }

    if (root == nullptr){
        root = new DepartmentNode(deptName, nullptr);
        count = 1;
        return true;
    }

    string parentTrimmed = TextHandler::trimmer(parentName);
    if(parentTrimmed.empty()){
        err = "Parent name can't be empty!";
        return false
    }
    DepartmentNode* parent = searchNode(parentTrimmed);
    if (parent == nullptr){
        err = "Unknrown Parent Department '" + parentTrimmer + "'.";
        return false;
    }

    parent->child.push_back(new DepartmentNode(deptName, parent));
    ++count;
    return true;
}

//loading departments.txt
DeptFileLoadingResult DepartmentTree::loadFromFile(const string& path){
    clear;
    DeptFileLoadingResult result = {0, 0, false};
    string file = findFileName(path);

    ifstream in(path.c_str());
    if(!in.is_open()){
        cout << "ERROR: Unable to open " << file << " (" << path << "), continuing without departments\n";
        summary(file, result);
        return result;
    }
    result.fileOpened = true;

    string line;
    size_t lineNumber = 0;
}


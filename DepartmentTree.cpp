//DepartmentTree.cpp (Impementing department tree ( load, add, search, trav, stats)
//F. Rodriguez
#include "DepartmentTree.h"
#include "TextHandler.h"
#include <fstream>
#include <iostream>
#include <queue>

namespace {
    const char* const ROT_PAR = "NONE"; //no parent to root..

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
        cout << file << " loaded: " << result.loaded << " accepted, " << result.rejected << " rejected.\n";
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
        return false;
    }
    DepartmentNode* parent = searchNode(parentTrimmed);
    if (parent == nullptr){
        err = "Unknrown Parent Department '" + parentTrimmed + "'.";
        return false;
    }

    parent->child.push_back(new DepartmentNode(deptName, parent));
    ++count;
    return true;
}

//loading departments.txt
DeptFileLoadingResult DepartmentTree::loadFromFile(const string& path){
    clear();
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
    while(getline(in, line)){
        ++lineNumber;

        //skip in UTF-8 byte, wowzas
        if (lineNumber == 1 && line.compare(0,3,"\xEF\xBB\xBF") == 0){
            line.erase(0,3);
        }

        string trimmed = TextHandler::trimmer(line);//BREAK TIME OVER :(
        if (trimmed.empty() || trimmed[0] == '#'){
            continue;
        }

        vector<string> fields = TextHandler::split(trimmed, '|');
        if (fields.size() != 2){
            rejectCatch(file, lineNumber, "expected 2 fields as follows (DepartmentName|ParentName), found " + to_string(fields.size()),result);
            continue;
        }
        string name = TextHandler::trimmer(fields[0]);
        string parent = TextHandler::trimmer(fields[1]);
        if (name.empty() || parent.empty()){
            rejectCatch(file, lineNumber, "missing field required", result);
            continue;
        }

        string err;
        bool validQ = false;
        bool isNone = TextHandler::eqIgnCase(parent, ROT_PAR);

        if(root==nullptr){
            if(!isNone){
                rejectCatch(file, lineNumber, "first department MUST be root, parent set as NONE. Parent is: " + parent, result);
                continue;
            }
            validQ = addDept(name, "", err);
        }
        else if(isNone && searchNode(parent) == nullptr){//allowing only NONE as root
            rejectCatch(file, lineNumber, name + " uses NONE, a root already exists, only one root please.", result);
            continue;
        }
        else{
            validQ = addDept(name, parent, err);
        }
        if(validQ){
            ++result.loaded;
        }
        else{
            rejectCatch(file, lineNumber, err, result);
        }
    }
    summary(file, result);
    return result;
}//loadFromFile should catch different anomolies such as missing fields, duplicates, and so on

//Edges from root, root is 0
int DepartmentTree::depth(const DepartmentNode* node) const{
    int edgeCount = 0;
    while (node != nullptr && node->par != nullptr){
        node = node->par;
        ++edgeCount;
    }
    return edgeCount;
}

//leaves in subtrees, nodes without children are leaves
size_t DepartmentTree::leavesRecursive(const DepartmentNode* node){
    if (node->child.empty()){
        return 1;
    }
    size_t leavesCount = 0;
    for(size_t i=0; i<node->child.size(); ++i){
        leavesCount += leavesRecursive(node->child[i]);
    }
    return leavesCount;
}

size_t DepartmentTree::leafCount() const {
    if (root == nullptr){
        return 0;
    }
    return leavesRecursive(root);
}

//Height of the subtrees using edges, a single node is 0
int DepartmentTree::heightRecursive(const DepartmentNode* node){
    int peak = 0;
    for(size_t i = 0; i < node->child.size(); ++i){
        int h = 1 + heightRecursive(node->child[i]);
        if(h > peak){
            peak = h;
        }
    }
    return peak;
}

//set -1 if the tree is empty
int DepartmentTree::height() const {
    if (root == nullptr){
        return -1;
    }
    return heightRecursive(root);
}

//prints departments line by line with 4 spaces in between depths, in preorder fashion
void DepartmentTree::dispRecursive(const DepartmentNode* node, int depth, ostream& out){
    out << string(static_cast<size_t>(depth) * 4 , ' ') << node->name << "\n";
    for(size_t i = 0; i < node->child.size(); ++i){
        dispRecursive(node->child[i], depth + 1, out);
    }
}

void DepartmentTree::displayDeptHier(ostream& out) const{
    if(root == nullptr){
        out << "No departments loaded.\n";
        return;
    }
    dispRecursive(root, 0, out);
}

//Preorder - Parent before L,R
void DepartmentTree::preRecursive(const DepartmentNode* node, vector<string>& out){
    out.push_back(node->name);
    for(size_t i =0; i< node->child.size(); ++i){
        preRecursive(node->child[i], out);
    }
}

vector<string> DepartmentTree::deptNamePre() const{
    vector<string> out;
    if (root != nullptr){
        preRecursive(root, out);
    }
    return out;
}

//Postoder - L,R before node
void DepartmentTree::postRecursive(const DepartmentNode* node, vector<string>& out){
    for(size_t i = 0; i < node->child.size(); ++i){
        postRecursive(node->child[i], out);
    }
    out.push_back(node->name);
}

//level order - bfs with q,child insert order
vector<string> DepartmentTree::deptNamePLevel() const {
    vector<string> out;
    if (root == nullptr){
        return out;
    }
    queue<const DepartmentNode*> upNext;
    upNext.push(root);
    while(!upNext.empty()){
        const DepartmentNode* node = upNext.front();
        upNext.pop();
        out.push_back(node->name);
        for(size_t i = 0; i < node->child.size(); ++i){
            upNext.push(node->child[i]);
        }
    }
    return out;
}

//fin

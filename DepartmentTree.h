//Department Tree (Tree of Depts,loads text from departments.txt, stats, and case insensitive search)
//F. Rodriguez
#ifndef DEPARTMENTTREE_H
#define DEPARTMENTTREE_H
#include "DepartmentNode.h"

#include <string>
#include <vector>
#include <cstddef> //size_t
#include <iosfwd> //setw
using namespace std;

struct DeptFileLoadingResult{
    size_t loaded;
    size_t rejected;
    bool fileOpened; //fileOpened = false if.. file not opened
};

class DepartmentTree{
    public:
        //def constr
        DepartmentTree();
        //destr
        ~DepartmentTree();

        //raw ptr pertains to tree, copying not allowed
        DepartmentTree(const DepartmentTree&) = delete;
        DepartmentTree& operator=(const DepartmentTree&) = delete;

        //replaces tree with file contents
        //load from file

        //add a dept (adddept or something)

        //case insensitive search, null if not found
        const DepartmentNode* findDept(const string& name) const;

        bool isEmpty() const;
        size_t size() const;

        //Edges from root, root = 0
        int depth(const DepartmentNode* node) const;

        //Amount of leaves and height
        size_t leafCount() const;
        int height() const;

        //display tree hierarchy
        void displayDeptHier(ostream& out) const;

        //Traversal for dept names, siblings will be visited in inserion order
        vector<string> deptNamePre() const;
        vector<string> deptNamePost() const;
        vector<string> deptNamePLevel() const;

        void clear();

    private:

        DepartmentNode* root;
        size_t count;

        DepartmentNode* searchNode(const string& name) const;

        static void delNode(DepartmentNode* node);
        static void preRecursive(const DepartmentNode* node, vector<string>& out);
        static void postRecursive(const DepartmentNode* node, vector<string>& out);
        static void dispRecursive(const DepatmentNode* node, int depth, ostream& out);
        static size_t leavesRecursive(const DepartmentNode* node);
        static int heightRecursive(const DepartmentNode* node);
};

#endif
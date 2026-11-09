//main.cpp (loading data files and running functions asked for M1)
//B. Cheruiyot, M. Oke, F. Rodriguez

#include "DepartmentTree.h" //file loading, dept adding, dept search, tree trav, stats
#include "DepartmentMenu.h" //department menu options
#include "TextHandler.h" //trimming, casing, splitting
/*^^^^^^
Include rest of h files above please
*/
#include <iostream>
#include <string>
/*^^^^^
also any other extensions if needed by your soecific parts
*/

//Printing the menu, in accordance to M1
void printMenu(){
    cout << "\n-----( Smart Campus Navigation )-----\n"<<"1. View all facilities\n"<<"2. Search facility by ID\n"<<"3. View campus graph\n"<<"4. Display graph counts and degrees\n"<<"5. Find  reachable buildings (BFS)"<<"6. Add departmnet\n"<<"7.Search department hierarchy\n"<<"8. Display department hierarchy\n"<<"9. Run preorder traversal\n"<<"0. Exit\n"<<"Enter choice > ";
}

//read function
int readChoice(){
    string line;
    if(!getline(cin, line)){
        cin.clear();
        return 0;
    }
    line = TextHandler::trimmer(line);
    if(line.empty() || line.size() > 2){
        return -1
    }
    for(size_t i = 0; i < line.size(); ++i){
        if(line[i] < '0' || line[i] > '9'){
            return -1;
        }
    }
    return stoi(line);//str to int
}

//placeholder function for other team members
void comingSoon(const string& x){
    cout << x << "is not available at the moment.. [module being connected]\n";
}

//takes data folder, loads with files
int main(int argc, char* argv[]){
    //data directory arg
    string dataDr = (argc > 1) ? argv[1] : "data";

    //required load order: buildings, connections, facilities, departments
    //Brenda (member A): facilities (buildings, connections, facilities loaded)
    //Michael (member B): campus graph

    int choice = -1;
    while(choice != 0){
        printMenu();
        choice = readChoice();
        switch(choice){
            case 1: comingSoon("View all facilities");
            break;
            case 2: comingSoon("Search facilitty by ID");
            break;
            case 3: comingSoon("View campus graph");
            break;
            case 4: comingSoon("Display graph counts and degrees");
            break;
            case 5: comingSoon("Find reachable buildings (BFS)");
            break;
            case 6: comingSoon("Add department");//DepartmentMenu::addDept(departments);
            break;
            case 7: comingSoon("Search department");//DepartmentMenu::searchDept(departments);
            break;
            case 8: comingSoon("Display departmnet hierarchy"); //DepartmentMenu::displayHier(departments);
            break;
            case 9: comingSoon("Run preorder trav");//DepartmentMenu::preorder(departments);
            break;
            case 0: cout << "Exiting, thank you using the Smart Campus Navigation System!\n";
            break;                                                                        
        }
    }

    return 0;
}
//main.cpp (loading data files and running functions asked for M1)
//B. Cheruiyot, M. Oke, F. Rodriguez

#include "DepartmentTree.h" //file loading, dept adding, dept search, tree trav, stats
#include "DepartmentMenu.h" //department menu options
#include "Facility.h"
#include "FacilityManager.h"
#include "LoadReport.h"
#include "TextHandler.h" //trimming, casing, splitting
#include "CampusGraph.h"
/*^^^^^^
Include rest of h files above please
*/
#include <iostream>
#include <string>
#include <vector>
/*^^^^^
also any other extensions if needed by your soecific parts
*/

//Printing the menu, in accordance to M1
void printMenu(){
    cout << "\n-----( Smart Campus Navigation )-----\n"<<"1. View all facilities\n"<<"2. Search facility by ID\n"<<"3. View campus graph\n"<<"4. Display graph counts and degrees\n"<<"5. Find  reachable buildings (BFS)\n"<<"6. Add department\n"<<"7.Search department\n"<<"8. Display department hierarchy\n"<<"9. Run preorder traversal\n"<<"0. Exit\n"<<"Enter choice > ";
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
        return -1;
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
    cout << x << " is not available at the moment.. [module being connected]\n";
}

//prompting
string promptUsr(const string& prompt){
    cout << prompt;
    string line;
    if(!getline(cin,line)){
        cin.clear();
        return "";
    }
    return TextHandler::trimmer(line);
}

//facilitiies printing
void printFacilities(const vector<Facility>& list, const string& emptyMsg){
    if(list.empty()){
        cout << emptyMsg<< endl;
        return;
    }
    for(size_t i = 0; i < list.size(); ++i){
        list[i].display();
    }
    cout << list.size() << " facility(ies) listed." <<endl;
}

//facility report
void printFacilityReport(const string& path, const LoadReport& report){
    cout << path << ": " << report.accepted << " accepted," << report.rejected << " rejected." << endl;
    for(size_t i =0; i < report.errors.size(); ++i){
        cout << " " << report.errors[i] << endl;
    }
}

//takes data folder, loads with files
int main(int argc, char* argv[]){
    //data directory arg
    string dataDr = (argc > 1) ? argv[1] : "data";

    //required load order: buildings, connections, facilities, departments
    //Brenda (member A): facilities (buildings, connections, facilities loaded)
    FacilityManager facilities;
    LoadReport faciReport = facilities.loadFromFile(dataDr + "/facilities.txt");
    printFacilityReport(dataDr + "/facilities.txt", faciReport);
    //Michael (member B): campus graph
    CampusGraph campusGraph;
    campusGraph.loadBuildings(dataDr + "/buildings.txt");
    campusGraph.loadConnections(dataDr + "/connections.txt");
    //Fernando (member C) departments
    DepartmentTree departments;
    departments.loadFromFile(dataDr + "/departments.txt");

    int choice = -1;
    while(choice != 0){
        printMenu();
        choice = readChoice();
        switch(choice){
            case 1: cout << "View all facilities";
            printFacilities(facilities.allFacilities(), "No facilities loaded.");
            break;

            case 2: comingSoon("Search facilitty by ID");
            break;

            case 3: // view campus graph
             campusGraph.displayGraph();
            break;

            case 4: // display graph counts & degrees
             campusGraph.displayStatistics();
            break;

            case 5: {
              cout << "Enter starting building: ";
              string start;
              getline(cin, start);

              start = TextHandler::trimmer(start);
               if (start.empty()) {
                   cout << "ERROR: Building name cannot be blank.\n";
               }
               else {
                   campusGraph.bfsReachability(start);
               }
            break;
            }
            
            case 6: DepartmentMenu::addDept(departments);
            break;

            case 7: DepartmentMenu::searchDept(departments);
            break;

            case 8: DepartmentMenu::displayHier(departments);
            break;

            case 9: DepartmentMenu::preorder(departments);
            break;

            case 0: cout << "Exiting, thank you using the Smart Campus Navigation System!\n";
            break;

            default: cout << "ERROR: Choice is invalid. Choose an option from 0 to 9!\n";
                                                                   
        }
    }

    return 0;
}

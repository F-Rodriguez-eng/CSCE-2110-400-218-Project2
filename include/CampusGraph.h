#ifndef CAMPUSGRAPH_H
#define CAMPUSGRAPH_H
#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

class CampusGraph {
private:
    vector<string> buildings;
    vector<vector<int>> neighbors;
    int edgeCount;
    int findBuilding(const string& name) const;
    bool hasEdge(int a, int b) const;

public:
    CampusGraph();
    bool addBuilding(const string& name);
    bool addConnection(const string& a, const string& b);
    string canonicalBuildingName(const string& name) const;
    void loadBuildings(const string& filename);
    void loadConnections(const string& filename);
    void displayGraph() const;
    void displayStatistics() const;
    void bfsReachability(const string& start) const;
    void shortestPath(const string& start,const string& destination) const;
    void connectivityReport() const;
};

#endif

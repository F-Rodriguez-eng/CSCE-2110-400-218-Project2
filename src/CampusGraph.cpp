// purpose: campus graph, connections, BFS, and reports
#include "CampusGraph.h"
#include "TextHandler.h"
#include <fstream>
#include <iostream>
#include <queue>
using namespace std;

// initializing graph
CampusGraph::CampusGraph() : edgeCount(0) {}

// IGNORE OUTER SPACE(S) + CAPITALIZATION
int CampusGraph::findBuilding(const string& name) const {
    string clean = TextHandler::trimmer(name);

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (TextHandler::eqIgnCase(buildings[i], clean)) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// connection check
bool CampusGraph::hasEdge(int a, int b) const {
    for (int index : neighbors[a]) {
        if (index == b) {
            return true;
        }
    }

    return false;
}

// accepted building returns next
string CampusGraph::canonicalBuildingName(const string& name) const {
    int index = findBuilding(name);

    if (index < 0) {
        return "";
    }

    return buildings[index];
}

// +building
bool CampusGraph::addBuilding(const string& name) {
    string clean = TextHandler::trimmer(name);

    if (clean.empty() ||
        clean.find('|') != string::npos ||
        findBuilding(clean) != -1) {
        return false;
    }

    buildings.push_back(clean);
    neighbors.push_back(vector<int>());

    return true;
}

bool CampusGraph::addConnection(const string& a, const string& b) {
    int x = findBuilding(a);
    int y = findBuilding(b);

    if (x < 0 || y < 0 || x == y || hasEdge(x, y)) {
        return false;
    }

    neighbors[x].push_back(y);
    neighbors[y].push_back(x);

    ++edgeCount;

    return true;
}

// loads/validates buildings.txt
void CampusGraph::loadBuildings(const string& filename) {
    buildings.clear();
    neighbors.clear();
    edgeCount = 0;

    ifstream file(filename.c_str());

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file) {
        cout << "Error: cannot open " << filename << "\n";
        cout << filename << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        ++lineNumber;

        string clean = TextHandler::trimmer(line);

        // blank line ignores
        if (clean.empty() || clean[0] == '#') {
            continue;
        }

        string reason;

        if (TextHandler::split(line, '|').size() != 1) {
            reason = "wrong number of fields";
        }
        else if (findBuilding(clean) >= 0) {
            reason = "duplicate building: " + clean;
        }

        if (reason.empty()) {
            if (addBuilding(clean)) {
                ++accepted;
            }
            else {
                reason = "invalid building name";
            }
        }

        if (!reason.empty()) {
            ++rejected;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": " << reason << "\n";
        }
    }

    cout << filename << ": "
         << accepted << " accepted, "
         << rejected << " rejected\n";
}

// loads/validates connections.txt
void CampusGraph::loadConnections(const string& filename) {
    for (size_t i = 0; i < neighbors.size(); ++i) {
        neighbors[i].clear();
    }

    edgeCount = 0;

    ifstream file(filename.c_str());

    int accepted = 0;
    int rejected = 0;
    int lineNumber = 0;

    if (!file) {
        cout << "Error: cannot open " << filename << "\n";
        cout << filename << ": 0 accepted, 0 rejected\n";
        return;
    }

    string line;

    while (getline(file, line)) {
        ++lineNumber;

        string clean = TextHandler::trimmer(line);

        if (clean.empty() || clean[0] == '#') {
            continue;
        }

        vector<string> parts = TextHandler::split(line, '|');
        string reason;

        if (parts.size() != 2) {
            reason = "wrong number of fields";
        }
        else {
            string a = TextHandler::trimmer(parts[0]);
            string b = TextHandler::trimmer(parts[1]);

            int x = findBuilding(a);
            int y = findBuilding(b);

            if (a.empty() || b.empty()) {
                reason = "empty building name";
            }
            else if (x < 0) {
                reason = "unknown building: " + a;
            }
            else if (y < 0) {
                reason = "unknown building: " + b;
            }
            else if (x == y) {
                reason = "self-connection";
            }
            else if (hasEdge(x, y)) {
                reason = "duplicate or reversed connection";
            }
            else if (addConnection(a, b)) {
                ++accepted;
            }
        }

        if (!reason.empty()) {
            ++rejected;

            cout << "Warning: " << filename
                 << " line " << lineNumber
                 << ": " << reason << "\n";
        }
    }

    cout << filename << ": "
         << accepted << " accepted, "
         << rejected << " rejected\n";
}

// portrays all buildings + neighbors
void CampusGraph::displayGraph() const {
    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); ++i) {
        cout << buildings[i] << ": ";

        if (neighbors[i].empty()) {
            cout << "(no connections)";
        }

        for (size_t j = 0; j < neighbors[i].size(); ++j) {
            if (j > 0) {
                cout << ", ";
            }

            cout << buildings[neighbors[i][j]];
        }

        cout << "\n";
    }
}

// portraying all buildings, connections, degrees
void CampusGraph::displayStatistics() const {
    cout << "Total buildings: " << buildings.size() << "\n";
    cout << "Total connections: " << edgeCount << "\n";

    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        return;
    }

    for (size_t i = 0; i < buildings.size(); ++i) {
        cout << buildings[i]
             << " - degree "
             << neighbors[i].size() << "\n";
    }
}

// BFS search
void CampusGraph::bfsReachability(const string& start) const {
    string clean = TextHandler::trimmer(start);

    if (clean.empty()) {
        cout << "Error: blank starting building.\n";
        return;
    }

    int source = findBuilding(clean);

    if (source < 0) {
        cout << "Error: unknown starting building: "
             << clean << "\n";
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> distance(buildings.size(), -1);
    queue<int> q;

    q.push(source);
    visited[source] = true;
    distance[source] = 0;

    int count = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        ++count;

        cout << buildings[current]
             << " (distance "
             << distance[current] << ")\n";

        // visiting unvisited (NEIGHBOR) buildings
        for (int next : neighbors[current]) {
            if (!visited[next]) {
                visited[next] = true;
                distance[next] = distance[current] + 1;
                q.push(next);
            }
        }
    }

    cout << "Reachable: " << count
         << " of " << buildings.size()
         << " buildings\n";
}

// FINAL: finding shortest path
void CampusGraph::shortestPath(
    const string& start,
    const string& destination) const {

    string a = TextHandler::trimmer(start);
    string b = TextHandler::trimmer(destination);

    if (a.empty() || b.empty()) {
        cout << "Error: blank building name.\n";
        return;
    }

    int source = findBuilding(a);
    int target = findBuilding(b);

    if (source < 0) {
        cout << "Error: unknown starting building: "
             << a << "\n";
        return;
    }

    if (target < 0) {
        cout << "Error: unknown destination building: "
             << b << "\n";
        return;
    }

    vector<bool> visited(buildings.size(), false);
    vector<int> parent(buildings.size(), -1);
    queue<int> q;

    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int next : neighbors[current]) {
            if (!visited[next]) {
                visited[next] = true;
                parent[next] = current;
                q.push(next);
            }
        }
    }

    if (!visited[target]) {
        cout << "No path exists between "
             << buildings[source] << " and "
             << buildings[target] << ".\n";
        return;
    }

    vector<int> reversedPath;

    for (int current = target; current != -1;
         current = parent[current]) {
        reversedPath.push_back(current);
    }

    for (size_t i = reversedPath.size(); i > 0; --i) {
        cout << buildings[reversedPath[i - 1]] << "\n";
    }

    cout << "Number of connections: "
         << reversedPath.size() - 1 << "\n";
}

// FINAL2: Connectivity report
void CampusGraph::connectivityReport() const {
    cout << "Total buildings: "
         << buildings.size() << "\n";

    cout << "Total connections: "
         << edgeCount << "\n";

    if (buildings.empty()) {
        cout << "No buildings are loaded.\n";
        cout << "Highest degree: N/A\n";
        cout << "Isolated buildings: None\n";
        cout << "Connected components: 0\n";
        return;
    }

    // highest degree location
    size_t maxDegree = 0;

    for (size_t i = 0; i < neighbors.size(); ++i) {
        if (neighbors[i].size() > maxDegree) {
            maxDegree = neighbors[i].size();
        }
    }

    cout << "Highest degree (" << maxDegree << "): ";

    bool printed = false;

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (neighbors[i].size() == maxDegree) {
            if (printed) cout << ", ";
            cout << buildings[i];
            printed = true;
        }
    }

    cout << "\nIsolated buildings: ";

    printed = false;

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (neighbors[i].empty()) {
            if (printed) cout << ", ";
            cout << buildings[i];
            printed = true;
        }
    }

    if (!printed) {
        cout << "None";
    }

    cout << "\n";

    // USE BFS
    vector<bool> visited(buildings.size(), false);
    int components = 0;

    for (size_t i = 0; i < buildings.size(); ++i) {
        if (!visited[i]) {
            ++components;

            queue<int> q;
            q.push(static_cast<int>(i));
            visited[i] = true;

            while (!q.empty()) {
                int current = q.front();
                q.pop();

                for (int next : neighbors[current]) {
                    if (!visited[next]) {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }
        }
    }

    cout << "Connected components: "
         << components << "\n";
}

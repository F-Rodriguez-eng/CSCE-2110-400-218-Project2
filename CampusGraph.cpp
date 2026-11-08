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

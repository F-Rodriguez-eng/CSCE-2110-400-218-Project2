#ifndef FACILITY_H
#define FACILITY_H
using namespace std;
#include <string>

// accepted campus facility record.
class Facility {
public:
    Facility(const string& id, const string& name,
             const string& category, const string& building);

    string getID() const;
    string getName() const;
    string getCategory() const;
    string getBuilding() const;

    void display() const;

private:
    string id;
    string name;
    string category;
    string building;
};

#endif

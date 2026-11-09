#include "Facility.h"
#include <iostream>
using namespace std;


Facility::Facility(const string& id, const string& name,
                   const string& category, const string& building)
    : id(id), name(name), category(category), building(building) {}

string Facility::getID() const { return id; }
string Facility::getName() const { return name; }
string Facility::getCategory() const { return category; }
string Facility::getBuilding() const { return building; }

void Facility::display() const {
    cout << "ID: " << id
              << " | Name: " << name
              << " | Category: " << category
              << " | Building: " << building << "\n";
}

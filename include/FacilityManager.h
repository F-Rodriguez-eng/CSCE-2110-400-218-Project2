#ifndef FACILITY_MANAGER_H
#define FACILITY_MANAGER_H

#include "Facility.h"
#include "FacilityHashTable.h"
#include "LoadReport.h"
#include <cstddef>
#include <map>
#include <string>
#include <vector>
using namespace std;//had #

class FacilityManager {
public:
    // To replace any previously loaded data.
    LoadReport loadFromFile(const string& path);
    //We need to be able to look up the Id by using hash table
    // Should be case-insensitive since IDs are stored upper-case

    const Facility* findByID(const string& id) const;

    // Use of linear search over accepted records
    vector<Facility> searchByName(const string& keyword) const;
    vector<Facility> searchByCategory(const string& category) const;

    // Number of accepted facilities per category
    map<string, size_t> categoryCounts() const;

    void displayCategoryReport() const;

    size_t totalFacilities() const;
    const FacilityHashTable& index() const;

    

private:
    FacilityHashTable table;
    // accepted records, in file order
    vector<Facility> records;  
};

#endif

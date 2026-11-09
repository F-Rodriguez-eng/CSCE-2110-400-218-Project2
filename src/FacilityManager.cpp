#include "FacilityManager.h"
#include "FileUtils.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;//had #


namespace {
//Records a problem of one line
void addError(LoadReport& report, size_t lineNo, const string& message) {
    ostringstream oss;
    oss << "Line " << lineNo << ": " << message;
    report.errors.push_back(oss.str());
    ++report.rejected;
}

}  
//Fills the list and the hash table
LoadReport FacilityManager::loadFromFile(const string& path) {
    //we need an empty table and listy
    table = FacilityHashTable();
    records.clear();

    LoadReport report;
    ifstream in(path.c_str());
    if (!in) {
        //if the file is not opened hence nothing to read
        report.errors.push_back("Cannot open file: " + path);
        return report;
    }
    //To read the file line to line
    string raw;
    size_t lineNo = 0;
    while (getline(in, raw)) {
        ++lineNo;
        //Removes spaces from the beginning and the end of the line
        string line = FileUtils::trim(raw);

        //skip blank and comment lines
        if (line.empty() || line[0] == '#') {
            continue;
        }
        //split a line with four parts
        vector<string> fields = FileUtils::split(line, '|');
        if (fields.size() != 4) {
            addError(report, lineNo, "expected 4 fields (ID|Name|Category|Building)");
            continue;
        }
        //Remove extra spaces
        for (string& field : fields) {
            field = FileUtils::trim(field);
        }
        if (fields[0].empty() || fields[1].empty() ||
            fields[2].empty() || fields[3].empty()) {
            addError(report, lineNo, "empty field");
            continue;
        }
        

        Facility facility(FileUtils::toUpper(fields[0]), fields[1], fields[2], fields[3]);

        //Adding to the hash table
        if (!table.insert(facility)) {
            //If its fails, the id already exists

            addError(report, lineNo, "duplicate facility ID " + facility.getID());
            continue;
        }
        records.push_back(facility);
        ++report.accepted;
    }
    return report;
}
//finding the facility ID using hash table
const Facility* FacilityManager::findByID(const string& id) const {
    return table.find(FileUtils::toUpper(FileUtils::trim(id)));
}
//finding the facilities by name
vector<Facility> FacilityManager::searchByName(const string& keyword) const {
    vector<Facility> results;

    //makes the keyword lower case
    string key = FileUtils::toLower(FileUtils::trim(keyword));
    if (key.empty()) {
        return results;
    }

    //checks every name
    for (const Facility& f : records) {
        if (FileUtils::toLower(f.getName()).find(key) != string::npos) {
            results.push_back(f);
        }
    }
    return results;
}

vector<Facility> FacilityManager::searchByCategory(const string& category) const {
    vector<Facility> results;
    string key = FileUtils::toLower(FileUtils::trim(category));
    if (key.empty()) {
        return results;
    }
    for (const Facility& f : records) {
        if (FileUtils::toLower(f.getCategory()) == key) {
            results.push_back(f);
        }
    }
    return results;
}

map<string, size_t> FacilityManager::categoryCounts() const {
    map<string, size_t> counts;
    for (const Facility& f : records) {
        ++counts[f.getCategory()];
    }
    return counts;
}

void FacilityManager::displayCategoryReport() const {
    cout << "\n=== CATEGORY REPORT ===\n";
    if (records.empty()) {
        cout << "No facilities loaded.\n";
        return;
    }

    cout << left << setw(20) << "Category"
              << setw(8) << "Count" << "Share\n";
    cout << string(40, '-') << "\n";

    for (const auto& entry : categoryCounts()) {
        double share = 100.0 * static_cast<double>(entry.second) /
                       static_cast<double>(records.size());
        cout << left << setw(20) << entry.first
                  << setw(8) << entry.second
                  << fixed << setprecision(1) << share << "%\n";
    }
    cout << string(40, '-') << "\n";
    cout << left << setw(20) << "Total" << records.size() << "\n";
}

size_t FacilityManager::totalFacilities() const { return records.size(); }

const FacilityHashTable& FacilityManager::index() const { return table; }

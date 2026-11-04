#include "FacilityHashTable.h"
#include <algorithm>
#include <cstdint>
using namespace std;

//Creating an hash table with initial bucket
FacilityHashTable::FacilityHashTable(size_t initialBuckets)
    : buckets(initialBuckets == 0 ? 1 : initialBuckets), count(0) {}

// Converting a facility ID into hash value
size_t FacilityHashTable::hashString(const string& key) {

    //start value
    uint32_t h = 2166136261u;


    for (unsigned char c : key) {
        h ^= c;
        h *= 16777619u;
    }
    return static_cast<size_t>(h);
}


//Add facility if the ID is not already there
bool FacilityHashTable::insert(const Facility& f) {

    //Reject duplicate IDs
    if (contains(f.getID())) {
        return false;
    }
    

    //Double the number of bucket
    if (static_cast<double>(count + 1) > 0.75 * static_cast<double>(buckets.size())) {
        rehash(buckets.size() * 2);
    }


    size_t index = hashString(f.getID()) % buckets.size();

    //stores the facility in the bucket
    buckets[index].push_back(f);
    ++count;//increased the number of facilities stored
    return true;
}

//looks for a facility by its Id
const Facility* FacilityHashTable::find(const std::string& id) const {
    const vector<Facility>& chain = buckets[hashString(id) % buckets.size()];
    
    //Search the facilities in the bucket
    for (const Facility& f : chain) {
        if (f.getID() == id) {
            return &f;
        }
    }
    return nullptr;// if no matching facility is found
}

//Returns true if the facility exists
bool FacilityHashTable::contains(const string& id) const {
    return find(id) != nullptr;
}

size_t FacilityHashTable::size() const { 
    return count; }//total number of facilities


size_t FacilityHashTable::bucketCount() const {
     return buckets.size(); }//total number of buckets

//shows empty buckets
size_t FacilityHashTable::emptyBucketCount() const {
    size_t empty = 0;
    for (const auto& chain : buckets) {
        if (chain.empty()) ++empty;
    }
    return empty;
}

size_t FacilityHashTable::longestChain() const {
    size_t longest = 0;
    for (const auto& chain : buckets) {
        longest = max(longest, chain.size());
    }
    return longest;
}


//Calculates the average number of facilities
double FacilityHashTable::loadFactor() const {
    return static_cast<double>(count) / static_cast<double>(buckets.size());
}

void FacilityHashTable::rehash(size_t newBucketCount) {
    vector<vector<Facility>> old;
    old.swap(buckets);
    buckets.assign(newBucketCount, vector<Facility>());
    for (const auto& chain : old) {
        for (const Facility& f : chain) {
            buckets[hashString(f.getID()) % newBucketCount].push_back(f);
        }
    }
}

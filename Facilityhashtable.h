#ifndef FACILITY_HASH_TABLE_H
#define FACILITY_HASH_TABLE_H

#include "Facility.h"
#include <cstddef>
#include <string>
#include <vector>
using namespace std;


// Custom hash table keyed by facility ID.
class FacilityHashTable {
public:
    explicit FacilityHashTable(size_t initialBuckets = 16);

    // Returns false (and stores nothing) if the ID already exists.
    bool insert(const Facility& f);

    // Returns a pointer to the matching record, or nullptr if absent.
    const Facility* find(const string& id) const;
    bool contains(const string& id) const;

    size_t size() const;
    size_t bucketCount() const;
    size_t emptyBucketCount() const;
    size_t longestChain() const;
    double loadFactor() const;

    static size_t hashString(const string& key);

private:
    vector<vector<Facility>> buckets;
    size_t count;

    void rehash(size_t newBucketCount);
};

#endif

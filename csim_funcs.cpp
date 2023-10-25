#include <cmath>
#include <iostream>
#include <sstream>
#include <vector>
#include "csim_funcs.h"

using namespace std;

bool has_invalid_param(int argc, char **argv) {

    int sets = stoi(argv[1]);
    int blocks = stoi(argv[2]);
    int bytes_in_block = stoi(argv[3]);
    std::string allocation = argv[4];
    std::string write_through = argv[5];
    std::string eviction = argv[6];

    /* Check for the following errors:
    * block size is not a power of 2
    * number of sets is not a power of 2
    * block size is less than 4
    * write-back and no-write-allocate were both specified
    */

    if (not_power_of_two(sets) || not_power_of_two(bytes_in_block)) {
        cerr << "Number of sets and block size must be a power of 2." << endl;
        return true;
    } else if (bytes_in_block < 4) {
        cerr << "Number of bytes in block must be at least 4." << endl;
        return true;
    } else if (allocation == "no-write-allocate" && write_through == "write-back") {
        cerr << "Write-back and no-write-allocate is not an available configuration."  << endl;
        return true;
    } else if (!(allocation == "no-write-allocate" || allocation == "write-allocate")) {
        cerr << "Specify no-write-allocate or write-allocate as parameter." << endl;
        return true;
    } else if (!(allocation == "write-through" || allocation == "write-back")) {
        cerr << "Specify write-through or write-back as parameter." << endl;
        return true;
    } else if (!(eviction == "lru" || eviction == "fifo")) {
        cerr << "Specify lru or fifo as parameter." << endl;
        return true;
    } else {
        return false;
    }
}

bool not_power_of_two(int num) {
    if (num <= 0) {
        return true;
    }
    return (num & (num - 1)) != 0;
}

Cache init_cache(char **argv) {
    int sets = stoi(argv[1]);
    int blocks = stoi(argv[2]);
    int bytes_in_block = stoi(argv[3]);
    std::string allocation = argv[4];
    std::string write_through = argv[5];
    std::string eviction = argv[6];

    int indexSize = log2(sets);
    int offsetSize = log2(blocks);
    unsigned int tagSize = 32 - indexSize - offsetSize;

    Cache cache;
    cache.sets.resize(sets);

    for (unsigned int i = 0; i < sets; i++) {
        cache.sets[i].slots.resize(blocks);
    }

    if (allocation == "write-allocate" && write_through == "write_through") {
        // allocate cache
    } else if (allocation == "write-allocate" && write_through == "write-back") {
        // allocate cache
    } else if (allocation == "no-write-allocate" && write_through == "write_through") {
        // allocate cache
    } else {
        // Theoretically, these params have been checked.
    }

    return cache;
}

int loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset) {
    return 1;
}

// Tag identifies the data block
// Index determines the set to find the data in
bool trace_is_a_hit(Cache* cache, uint32_t tag, uint32_t index) {
    // Check if the cache set at the specified index is empty
    if (cache->sets[index].slots.empty()) {
        // Cache miss: The set is empty, so there can be no hits
        return false;
    }

    // Iterate through the slots in the cache set
    for (const Slot& slot : cache->sets[index].slots) {
        if (slot.valid && slot.tag == tag) {
            // Cache hit: The data with the specified tag is found in the cache set
            return true;
        }
    }

    // Cache miss: The data with the specified tag is not found in the cache set
    return false;
}

void read_trace(Cache* cache, uint32_t index, uint32_t tag) {
    if (trace_is_a_hit(cache, index, tag)) {
        
    }
}
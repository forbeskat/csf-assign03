#include <cmath>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <string.h>
#include "csim_funcs.h"

using namespace std;

// write-allocate = store miss
// get address from memory and then store, 

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
    } else if (!(write_through == "write-through" || write_through == "write-back")) {
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
    int blocks = stoi(argv[2]); // blocks = slotsSize
    int bytes_in_block = stoi(argv[3]); // blockSize
    std::string allocation = argv[4];
    std::string write_through = argv[5];
    std::string eviction = argv[6];

    int indexSize = log2(sets);
    int offsetSize = log2(blocks);
    unsigned int tagSize = 32 - indexSize - offsetSize;

    Cache cache;
    cache.numslots = stoi(argv[2]);
    cache.numsets = stoi(argv[3]);

    cache.sets.resize(sets);

    for (unsigned int i = 0; i < sets; i++) {
        cache.sets[i].slots.resize(blocks);
    }
    

    // cache.num_sets = sets;
    // cache.num_blocks_per_set = blocks;
    // cache.num_bytes_per_block = bytes_in_block;

    // cache.is_write_allocate = (strcmp(argv[4], "write-allocate") == 0);
    // cache.is_write_through = (strcmp(argv[5], "write-through") == 0);
    // cache.is_lru = ((strcmp(argv[6], "lru") == 0));

    // cache.tracker["total_loads"] = 0;
    // cache.tracker["total_stores"] = 0;
    // cache.tracker["load_hits"] = 0;
    // cache.tracker["store_hits"] = 0;
    // cache.tracker["store_misses"] = 0;
    // cache.tracker["total_cycles"] = 0;

    // if (allocation == "write-allocate" && write_through == "write_through") {
    //     // allocate cache
    // } else if (allocation == "write-allocate" && write_through == "write-back") {
    //     // allocate cache
    // } else if (allocation == "no-write-allocate" && write_through == "write_through") {
    //     // allocate cache
    // } else {
    //     // Theoretically, these params have been checked.
    // }

    return cache;
}

// Tag identifies the data block
// Index determines the set to find the data in
bool trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int slotSize, unsigned int loopCounter, const char* eviction) {
    // Check if the cache set at the specified index is empty
    //string here = cache->sets[index].slots[0].valid ? "true" : "false";
    //cout<<here<<endl;
    // if (cache->sets[index].slots.empty()) {
    //     // Cache miss: The set is empty, so there can be no hits
    //     return false;
    // }

    for (unsigned int i = 0; i < slotSize; i++) {
        if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
            if (strcmp(eviction, "lru") == 0) {
                cache->sets[index].slots[i].access_ts = loopCounter; //UPDATE ACCESS TIMESTAMP;
            }
            
            //cout<<cache->sets[index].slots[i].tag<<endl;
            
            return true;
        }
    }
    // Cache miss: The data with the specified tag is not found in the cache set
    return false;
}

// Store -> memory in cache (DONE)
void storeHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wHit, unsigned int loopCounter, unsigned int* store_hits) {
    // *total_cycles = *total_cycles + 1;
    *store_hits = *store_hits + 1;
    // for (unsigned int i = 0; i < slotSize; i++) {
    //     if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
    //         cache->sets[index].slots[i].access_ts = loopCounter; //UPDATE ACCESS TIMESTAMP;
    //         // increase total cycles when eviction occurs to account for the write back to memory
    //     }
    // }

    if (strcmp(wHit, "write-through") == 0) {
        *total_cycles += 100; //(100 * bytes_in_block / 4);
        // return;
    } else if (strcmp(wHit, "write-back") == 0) {
        writeBack(cache, index, tag, slotSize, total_cycles, bytes_in_block);
        return;
    }
}

// Store -> memory not in cache (NOT DONE!!!!)
void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char *wMiss, const char *wHit, unsigned int loopCounter, unsigned int* store_misses, const char* eviction) {
    *store_misses = *store_misses + 1;
    if (strcmp(wMiss, "write-allocate") == 0) {
        // we bring the relevant memory block into the cache before the store proceeds, takes 100 processor cycles
        *total_cycles = *total_cycles + ((100 * bytes_in_block / 4) / 4);
        // put into a new slot, write it into the cache
        checkForOpenSlot(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);
        // *total_cycles = *total_cycles + 1;
        if (strcmp(wHit, "write-through") == 0) {
            *total_cycles = *total_cycles + ((100 * bytes_in_block / 4) / 4);
        } else if (strcmp(wHit, "write-back") == 0) {
            writeBack(cache, index, tag, slotSize, total_cycles, bytes_in_block);
        }
        
    } else if (strcmp(wMiss, "no-write-allocate") == 0) {
        // modify in memory
        *total_cycles += (100 * bytes_in_block / 4);
        return;
    }
}

// a store writes to the cache only and marks the block dirty; if the block is evicted later, it has to be written back to memory before being replaced
void writeBack(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block) {
    for (unsigned int i = 0; i < slotSize; i++) {
        if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
            cache->sets[index].slots[i].dirty = true;
            // increase total cycles when eviction occurs to account for the write back to memory
        }
    }
}

// Load -> memory found in cache. We just need to update the time stamp.
void loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, unsigned int* load_hits) {
    *load_hits = *load_hits + 1;
    // for (unsigned int i = 0; i < slotSize; i++) {
    //     if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
    //         cache->sets[index].slots[i].access_ts = cache->counter; //UPDATE ACCESS TIMESTAMP;
    //         // increase total cycles when eviction occurs to account for the write back to memory
    //         return;
    //     }
    // }
}

// Load -> memory not found in cache. This means that memory needs to be brought to the cache and then memory needs to be stored to the cache.
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wMiss, unsigned int loopCounter, unsigned int* load_misses, const char* eviction) {
    *total_cycles = *total_cycles + (100 * bytes_in_block / 4);
    *load_misses = *load_misses + 1;
    // Create a new slot by replacing an invalid block in the cache
    checkForOpenSlot(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);
    // *total_cycles = *total_cycles + 1;
}

void checkForOpenSlot(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int * total_cycles, unsigned int loopCounter, const char* eviction) {
    // If slot is availble, add it to the cache
    for (unsigned int i = 0; i < slotSize; i++) {
        if (cache->sets[index].slots[i].valid == false) {
            cache->sets[index].slots[i].valid = true;
            cache->sets[index].slots[i].tag = tag;
            cache->sets[index].slots[i].access_ts = loopCounter;
            cache->sets[index].slots[i].dirty = false;
            return;
        }
    }

    // If there is no slot available, we need to evict one and replace it
    evict(cache, index, tag, slotSize, total_cycles, loopCounter);
}

// vector<int> findFIFO(Cache *cache, unsigned int loop_counter) {
//     return NULL;
// }

// vector<int> findLRU(Cache *cache, unsigned int loop_counter) {
//     vector<int> lru(3); //set index, slot index, access timemstap
//     lru.at(2) = loop_counter;
//     for (int i =0; i< cache->numsets; i++){
//         for (int j =0; j<cache->numslots; j++){
//             if ((int)(cache->sets[i].slots[j].access_ts) < lru.at(2)){
//                 lru.at(0)= i;
//                 lru.at(1)= j;
//                 lru.at(2)= cache->sets[i].slots[j].access_ts; //least access ts is the lru
//             }
//         }
//     }
//     return lru;
// }

void evict(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int * total_cycles, unsigned int loop_counter) { //evict and replace
    //vector<int> lru = findLRU(cache, loop_counter);

    //following below pseudocode
    Slot *evict = NULL;
    int min = 2147483647;
    for (int i = 0; i< cache->numslots; i++){
        if (cache->sets[index].slots[i].access_ts < min) {
            evict = &cache->sets[index].slots[i];
            min = cache->sets[index].slots[i].access_ts;
        }
    }
    evict->valid = true;
    evict->tag = tag;
    evict->access_ts = loop_counter;
    
    if (evict->dirty == true) {
        *total_cycles = *total_cycles + (100 * slotSize / 4);
    }

    evict->dirty = false;

    //evict->dirty = false;
    

    // Slot * slot-to-evict = NULL;
    // int min = max integer values
    // loop through all slots at set[index]
    //    compare the access timestamp to min
    //    if smaller
    //    then set *slot-to-evict = sets[index].slots[i]
    //    and min = sets[index].slots[i].access_ts

    // then do slot-to-evict->tag = tag
    // slot-to-evict.valid = true, etc. (what you have below)


    // cache->sets[lru.at(0)].slots[lru.at(1)].valid = true;
    // cache->sets[lru.at(0)].slots[lru.at(1)].tag = tag;
    // cache->sets[lru.at(0)].slots[lru.at(1)].access_ts = loop_counter;
    // cache->sets[lru.at(0)].slots[lru.at(1)].dirty = true;
}

void set_counter(Cache* cache, unsigned int counter) {
    cache->counter = counter;
}
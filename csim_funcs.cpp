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

    return cache;
}

// Tag identifies the data block
// Index determines the set to find the data in
bool trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int slotSize, unsigned int loopCounter, const char* eviction) {
    if (cache->sets[index].slots.empty()) {
        // Cache miss: The set is empty, so there can be no hits
        return false;
    }

    for (unsigned int i = 0; i < slotSize; i++) {
        //if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
        if (cache->sets[index].slots[i].tag == tag) {
            if (strcmp(eviction, "lru") == 0) {
                cache->sets[index].slots[i].access_ts = loopCounter; //UPDATE ACCESS TIMESTAMP;
            }

            //else{//fifo}
            return true;
        }
    }
    // Cache miss: The data with the specified tag is not found in the cache set
    return false;
}


//literally the same thing but no update access ts
bool trace_is_a_hit_s(Cache* cache, unsigned int tag, unsigned int index, unsigned int slotSize, unsigned int loopCounter, const char* eviction) {
    for (unsigned int i = 0; i < slotSize; i++) {
        if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
            // cache->sets[index].slots[i].dirty=true;
            return true;
        }
    }
    return false;
}

// Store -> memory in cache (DONE)
void storeHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wHit, unsigned int loopCounter, unsigned int* store_hits) {
    // *total_cycles = *total_cycles + 1;
    *store_hits = *store_hits + 1;
    if (strcmp(wHit, "write-through")){
        (*total_cycles)+=(100-1);
    } else{
        (*total_cycles) += 1;
        checkForOpenSlot_wb(cache, index, tag, slotSize, total_cycles, loopCounter, "lru");
    }

    //is this thing tru
    // if (strcmp(wHit, "write-back")){
    //     *total_cycles += 100;//(100 * bytes_in_block / 4);
    //     writeBack(cache, index, tag, slotSize, total_cycles, bytes_in_block);
    // }
}

// Store -> memory not in cache (NOT DONE!!!!)
void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char *through_back, const char *allocate, unsigned int loopCounter, unsigned int* store_misses, const char* eviction) {
    *store_misses = *store_misses + 1;
    //update write to memory
    
    if (strcmp(allocate,"write-allocate")!=0){ //no allocate => write through
        (*total_cycles) +=(100-1);
        return;
    } else{
        // (*total_cycles) += (100 * bytes_in_block / 4);
        (*total_cycles)+=1;
        if(strcmp(through_back,"write-through")==0){ //write allocate + write through
            (*total_cycles)+=100;
            checkForOpenSlot(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);
        } else{ //write allocate + write back
            checkForOpenSlot_wb(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);
        }
    }


    //checkForOpenSlot(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);

}

// Load -> memory found in cache. We just need to update the time stamp.
void loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, unsigned int* load_hits, const char* wHit) {
    *load_hits = *load_hits + 1;
    cache->sets[index].slots[tag].access_ts = cache->counter;

    // if (strcmp(wHit,"write-through") == 0) {
    //     *total_cycles += 100;//(100 * bytes_in_block / 4);
    //     // return;
    // } else if (strcmp(wHit, "write-back") == 0) {
    //     writeBack(cache, index, tag, slotSize, total_cycles, bytes_in_block);
    //     return;
    // }
}

// Load -> memory not found in cache. This means that memory needs to be brought to the cache and then memory needs to be stored to the cache.
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wMiss, unsigned int loopCounter, unsigned int* load_misses, const char* eviction) {
    *total_cycles = *total_cycles + (100 * bytes_in_block / 4);
    *load_misses = *load_misses + 1;

    checkForOpenSlot(cache, index, tag, slotSize, total_cycles, loopCounter, eviction);
    //adjust load timer too????
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
    //evict(cache, index, tag, slotSize, total_cycles, loopCounter);
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
    evict->access_ts = loopCounter;
    
    if (evict->dirty == true) { //slot is dirty so write to memory
        *total_cycles = *total_cycles + (100 * slotSize / 4);
    }
    evict->dirty = false; //should match memory now

    
}

void checkForOpenSlot_wb(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int * total_cycles, unsigned int loopCounter, const char* eviction) {
    //literally the same thing but with dirty = true

    // If slot is availble, add it to the cache
    for (unsigned int i = 0; i < slotSize; i++) {
        if (cache->sets[index].slots[i].valid == false) {
            cache->sets[index].slots[i].valid = true;
            cache->sets[index].slots[i].tag = tag;
            cache->sets[index].slots[i].access_ts = loopCounter;
            //cache->sets[index].slots[i].dirty = false;
            cache->sets[index].slots[i].dirty = false;
            return;
        }
    }
    
    // If there is no slot available, we need to evict one and replace it
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
    evict->access_ts = loopCounter;
    //evict->dirty=true;

    
}


void set_counter(Cache* cache, unsigned int counter) {
    cache->counter = counter;
}


// LoadHit -> write-back and write-allocate
// 
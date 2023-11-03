#include <cmath>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <vector>
#include <string.h>
#include "csim_funcs.h"
using namespace std;

bool has_invalid_param(char **argv) {
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
    unsigned int sets = stoi(argv[1]);
    unsigned int blocks = stoi(argv[2]); // blocks = slotsSize
    // int bytes_in_block = stoi(argv[3]); // blockSize
    std::string write_allocate = argv[4];
    std::string through_or_back = argv[5];
    std::string eviction = argv[6];
    //int indexSize = log2(sets);
    //int offsetSize = log2(blocks);
    //unsigned int tagSize = 32 - indexSize - offsetSize;
    Cache cache;
    cache.numsets = stoi(argv[1]); 
    cache.numslots = stoi(argv[2]);
    cache.numbytes = stoi(argv[3]);
    
    cache.replacement = argv[6];
    cache.sets.resize(sets);

    for (unsigned int i = 0; i < sets; i++) {
        cache.sets[i].slots.resize(blocks);
    }
    if (write_allocate == "write-allocate") {
        cache.is_write_allocate = true;
    }
    if (through_or_back == "write-back") {
        cache.is_write_back = true;
    } 
    return cache;
}

// return the value of the slot that is a hit if there is a hit
Slot* val_trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int blockSize) {
    for (unsigned int i = 0; i < blockSize; i++) {
        if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
            cache->sets[index].slots[i].access_ts = cache->counter;
            return &cache->sets[index].slots[i];
        }
    }
    return NULL;
}

//we know that load missed. so we need to find an open slot in the set. first check if any with valid = false. if not then just evict something
Slot* find_open_slot(Cache *cache, unsigned int index, string replacement) {
    for (unsigned int i = 0; i < cache->numslots; i++){
        if (!(cache->sets[index].slots[i].valid)){
            return &cache->sets[index].slots[i];
        }
    }

    unsigned int min = UINT_MAX; //represents the minimum timestamp we encounter
    Slot *evict = NULL; //now that we are here we have to find something to evict
    if (replacement == "lru"){
        for (unsigned int i = 0; i < cache->numslots; i++){
            if (cache->sets[index].slots[i].access_ts < min) { //for lru we look at access ts
                evict = &cache->sets[index].slots[i];
                min = cache->sets[index].slots[i].access_ts;
            }
        }
    } else { //fifo
        for (unsigned int i = 0; i < cache->numslots; i++){ //for fifo we look at load ts
            if (cache->sets[index].slots[i].load_ts < min) {
                evict = &cache->sets[index].slots[i];
                min = cache->sets[index].slots[i].load_ts;
            }
        }
    }
    return evict;
}

// Load -> memory found in cache. We just need to update the time stamp.
void loadHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* load_hits) {
    *load_hits = *load_hits + 1;
    *total_cycles = *total_cycles + 1;
    slot->access_ts = cache->counter;
}

// Load -> memory not found in cache. This means that memory needs to be brought to the cache and then memory needs to be stored to the cache.
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int loopCounter, unsigned int* load_misses) {
    *total_cycles = *total_cycles + (100 * cache->numbytes / 4);
    *load_misses = *load_misses + 1;
    Slot* victim = find_open_slot(cache, index, cache->replacement);

    if (victim->valid && cache->is_write_back && victim->dirty) {
        *total_cycles = *total_cycles + (100 * cache->numbytes / 4);
    }
    
    reassign(cache, victim, tag);
    victim->dirty = false;
}

// Store -> memory found in cache. We just need to update the time stamp and possibly some other stuff
void storeHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* store_hits) {
    // *total_cycles = *total_cycles + 1;
    *store_hits = *store_hits + 1;

    if (!cache->is_write_allocate && !cache->is_write_back) {
        *total_cycles = *total_cycles + 100;
    } else if (cache->is_write_allocate && !cache->is_write_back) {
        slot->access_ts = cache->counter;
        slot->dirty = true;
        *total_cycles = *total_cycles + 100;
    } else {
        slot->access_ts = cache->counter;
        slot->dirty = true;
        *total_cycles = *total_cycles + 1;
    }

    // if (!cache->is_write_back){
    //     (*total_cycles) += (100);
    // } else {
    //     slot->dirty = true;
    // }
}

// Store -> memory not found in cache. This means that we have to do some other stuff
void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int loopCounter, unsigned int* store_misses) {
    *store_misses = *store_misses + 1;
    
    if (!cache->is_write_allocate && !cache->is_write_back) { // No-write-allocate + write-through
        *total_cycles = *total_cycles + 100;
        return; // Do nothing
    }
    
    Slot *slot = find_open_slot(cache, index, cache->replacement);
    *total_cycles = *total_cycles + (100 * cache->numbytes / 4);// cost of loading block
    if (slot->valid && cache->is_write_back && slot->dirty) {
        *total_cycles = *total_cycles + (100 * cache->numbytes / 4); // cost of writing back dirty block
    }

    if (cache->is_write_allocate && !cache->is_write_back) { // Write-allocate + write-through
        reassign(cache, slot, tag);
        *total_cycles = *total_cycles + 100;
    } else { // Write-allocate + write-back
        reassign(cache, slot, tag);
        slot->dirty = true;
        *total_cycles = *total_cycles + 1;
    }

    // if (!cache->is_write_allocate && !cache->is_write_back) { // No-write-allocate + write-through
    //     return; // Do nothing
    // } else if (cache->is_write_allocate && !cache->is_write_back) { // Write-allocate + write-through
    //     Slot *victim = find_open_slot(cache, index, cache->replacement);
    //     reassign(cache, victim, tag);
    // } else { // Write-allocate + write-back
    //     Slot *victim = find_open_slot(cache, index, cache->replacement);
    //     reassign(cache, victim, tag);
    // }

    ///////////////////

    // if (!cache->is_write_allocate) { //no allocate (write through)
    //     (*total_cycles) += (100);
    //     return;

        
    // } else if (cache->is_write_allocate){
    //     // (*total_cycles) += (100 * bytes_in_block / 4);
    //     (*total_cycles) += 1;
    //     if (cache->is_write_back) { //write allocate + write back
    //         (*total_cycles) ++;

    //         Slot *victim = find_open_slot(cache, index, cache->replacement);
    //         reassign(cache, victim, tag);
    //         victim->dirty = true;

    //     } else { //write allocate + write through
    //         (*total_cycles) += 100;
            
    //         Slot *victim = find_open_slot(cache, index, cache->replacement);
    //         reassign(cache, victim, tag);
    //     }
    // }
} 

void reassign(Cache* cache, Slot *victim, unsigned int tag) {
    victim->access_ts = cache->counter;
    victim->load_ts = cache->counter;
    victim->tag = tag;
    victim->valid = true;
    victim->dirty = false;
}

//update counter in cache
void set_counter(Cache* cache, unsigned int counter) {
    cache->counter = counter;
}
#include <cmath>
#include <cstring>
#include <iostream>
#include <limits.h>
#include <sstream>
#include <vector>
#include <string.h>
#include "csim_funcs.h"
using namespace std;

//check for any possible errors in the command line arguments
bool has_invalid_param(char **argv) {
    std::string allocation = argv[4];
    std::string write_through = argv[5];
    std::string eviction = argv[6];
    if (not_power_of_two(stoi(argv[1])) || not_power_of_two(stoi(argv[3]))) {
        cerr << "Number of sets and block size must be a power of 2." << endl;
        return true;
    } else if (stoi(argv[3]) < 4) {
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
    } else { return false;}
}

bool not_power_of_two(int num) {
    if (num <= 0) { return true;}
    return (num & (num - 1)) != 0;
}

Cache init_cache(char **argv) {
    Cache cache;
    cache.numsets = stoi(argv[1]); 
    cache.numslots = stoi(argv[2]);
    cache.numbytes = stoi(argv[3]);
    std::string write_allocate = argv[4];
    std::string through_or_back = argv[5];
    cache.replacement = argv[6];
    cache.sets.resize(cache.numsets);
    for (unsigned int i = 0; i < cache.numsets; i++) { cache.sets[i].slots.resize(cache.numslots);}
    if (write_allocate == "write-allocate") { cache.is_write_allocate = true;}
    if (through_or_back == "write-back") { cache.is_write_back = true;} 
    return cache;
}

Slot* val_trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int blockSize) {
    for (unsigned int i = 0; i < blockSize; i++) {
        if (cache->sets[index].slots[i].valid == true && cache->sets[index].slots[i].tag == tag) {
            cache->sets[index].slots[i].access_ts = cache->counter;
            return &cache->sets[index].slots[i];
        }
    }
    return NULL;
}

Slot* find_open_slot(Cache *cache, unsigned int index, string replacement) {
    for (unsigned int i = 0; i < cache->numslots; i++){
        if (!(cache->sets[index].slots[i].valid)){
            return &cache->sets[index].slots[i];
        }
    }
    Slot *evict = NULL; //now that we are here we have to find something to evict
    unsigned int min = UINT_MAX; //will represent the minimum timestamp we encounter (at the end we evict the one that has min)
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

void loadHit( unsigned int* total_cycles, unsigned int* load_hits) {
    *load_hits = *load_hits + 1;
    *total_cycles = *total_cycles + 1; //loads/stores from/to the cache take one processor cycle
}

void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* load_misses) {
    *total_cycles = *total_cycles + (100 * cache->numbytes / 4); //loads/stores from/to memory take 100 processor cycles for each 4-byte quantity that is transferred
    *load_misses = *load_misses + 1;
    Slot* victim = find_open_slot(cache, index, cache->replacement);
    if (victim->valid && cache->is_write_back && victim->dirty) {
        *total_cycles = *total_cycles + (100 * cache->numbytes / 4); // cost of writing back dirty block
    }
    reassign(cache, victim, tag); //we know there was no hit, so we need to add it to the cache
}

void storeHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* store_hits) {
    *store_hits = *store_hits + 1;
    if (!cache->is_write_allocate && !cache->is_write_back) {
        *total_cycles = *total_cycles + 100; //cost of write-through to memory
    } else if (cache->is_write_allocate && !cache->is_write_back) {
        slot->dirty = true;
        *total_cycles = *total_cycles + 100; //cost of write-through to memory
    } else {
        slot->dirty = true;
        *total_cycles = *total_cycles + 1; //loads/stores from/to the cache take one processor cycle
    }
}

void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* store_misses) {
    *store_misses = *store_misses + 1;
    if (!cache->is_write_allocate && !cache->is_write_back) { // No-write-allocate + write-through
        *total_cycles = *total_cycles + 100; //cost of write-through to memory
        return; // Do nothing
    }
    //write-allcoate: we know there was no hit, so we need to add it to the cache
    Slot *slot = find_open_slot(cache, index, cache->replacement);
    *total_cycles = *total_cycles + (100 * cache->numbytes / 4);//loads/stores from/to memory take 100 processor cycles for each 4-byte quantity that is transferred
    if (slot->valid && cache->is_write_back && slot->dirty) {
        *total_cycles = *total_cycles + (100 * cache->numbytes / 4); // cost of writing back dirty block
    }
    if (cache->is_write_allocate && !cache->is_write_back) { // Write-allocate + write-through
        reassign(cache, slot, tag);
        *total_cycles = *total_cycles + 100; //cost of write-through to memory
    } else { // Write-allocate + write-back
        reassign(cache, slot, tag);
        slot->dirty = true;
        *total_cycles = *total_cycles + 1; //loads/stores from/to the cache take one processor cycle
    }
} 

void reassign(Cache* cache, Slot *victim, unsigned int tag) {
    victim->access_ts = cache->counter;
    victim->load_ts = cache->counter;
    victim->tag = tag;
    victim->valid = true;
    victim->dirty = false;
}
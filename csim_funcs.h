#ifndef CSIM_FUNCS
#define CSIM_FUNCS

#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct Slot {
    unsigned int tag = 0;
    unsigned int access_ts = 0;
    unsigned int load_ts = 0;
    bool valid = false;
    bool dirty = false;
};

struct Set {
    std::vector<Slot> slots;
};

struct Cache {
    vector<Set> sets;
    unsigned int numslots;
    unsigned int numsets;
    unsigned int numbytes;
    int counter = 0;
    string replacement;
    bool is_write_back = false;
    bool is_write_allocate = false;
};

/* Check if parameters are valid */
bool has_invalid_param(char **argv);

/* Used to check if user param is a power of 2 */
bool not_power_of_two(int num);

/* Initialize the cache according to the configurations given by user */
Cache init_cache(char **argv);

// if there is a hit, return the slot that is a hit and update its time stamp
Slot* val_trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int blockSize);

//find the next available slot in the set or evict to create an open slot if necessary
//we know that there was not a hit. so we need to find an open slot in the set, and if there is none, we just evict something
Slot* find_open_slot(Cache *cache, unsigned int index, string replacement);

//handle load when there is a hit
// Load -> memory found in cache. We just need to uupdate load hits and total cycles.
void loadHit(unsigned int* total_cycles, unsigned int* load_hits);

//handle load when there is a miss 
// Load -> memory not found in cache. This means that memory needs to be brought to the cache and then memory needs to be stored to the cache.
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* load_misses);

//handle store when there is a hit
// Store -> memory found in cache. update store hits and handle dirty/total cycles based on provided parameters.
void storeHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* store_hits);

//handle store when there is a miss
//Store -> memory not found in cache. update store misses and handle adding a new element/dirty/total cycles based on provided parameters.
void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* store_misses);

//update a victim slot
//change the information in victim slot to effectively reassign it
void reassign(Cache* cache, Slot *victim, unsigned int tag);

#endif
#ifndef CSIM_FUNCS
#define CSIM_FUNCS

#include <string>
#include <iostream>
#include <map>
#include <vector>
//#include "sets_and_slots.h"

using namespace std;

struct Slot {
    unsigned int tag = 0;
    unsigned int access_ts = 0; // timestamps
    unsigned int load_ts = 0;
    bool valid = false;
    bool dirty = false;
};

struct Set {
    std::vector<Slot> slots;
};

struct Cache {
    vector<Set> sets;
    int numslots;
    int numsets;
    int counter = 0;
};

/* Check if parameters are valid */
bool has_invalid_param(int argc, char **argv);

/* Used to check if user param is a power of 2 */
bool not_power_of_two(int num);

/* Initialize the cache according to the configurations given by user */
Cache init_cache(char **argv);

bool trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int slotSize, unsigned int loopCounter, const char* eviction);

void storeHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wHit, unsigned int loopCounter, unsigned int* store_hits);

void loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, unsigned int* load_hits, const char* wHit);

void writeBack(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block);

void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char *wMiss, const char *wHit, unsigned int loopCounter, unsigned int* store_misses, const char* eviction);

void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int bytes_in_block, const char* wMiss, unsigned int loopCounter, unsigned int* load_misses, const char* eviction);

void checkForOpenSlot(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int* total_cycles, unsigned int loopCounter, const char* eviction);

void evict(Cache *cache, unsigned int index, unsigned int tag, unsigned int slotSize, unsigned int * total_cycles, unsigned int loopCounter);

void set_counter(Cache* cache, unsigned int counter);

// vector<int> findFIFO(Cache *cache, unsigned int loop_counter);

// vector<int> findLRU(Cache *cache, unsigned int loop_counter);

// void read_trace(unsigned int index, unsigned int tag);


#endif
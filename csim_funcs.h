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

Slot* val_trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int blockSize);

Slot* find_open_slot(Cache *cache, unsigned int index, string replacement);

void loadHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* load_hits);

// 7 params
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int loopCounter, unsigned int* load_misses);

void storeHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int loopCounter, unsigned int* store_hits);

void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int loopCounter, unsigned int* store_misses);

void set_counter(Cache* cache, unsigned int counter);


#endif
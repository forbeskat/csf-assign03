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

//return the value of the slot that is a hit if there is a hit
Slot* val_trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index, unsigned int blockSize);

//find the next available slot in the set or evict to create an open slot if necessary
Slot* find_open_slot(Cache *cache, unsigned int index, string replacement);

//handle load when there is a hit
void loadHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* load_hits);

//handle load when there is a miss
void loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* load_misses);

//handle store when there is a hit
void storeHit(Cache* cache, Slot* slot, unsigned int* total_cycles, unsigned int* store_hits);

//handle store when there is a miss
void storeMiss(Cache *cache, unsigned int index, unsigned int tag, unsigned int* total_cycles, unsigned int* store_misses);

//update a victim slot
void reassign(Cache* cache, Slot *victim, unsigned int tag);

//update counter
void set_counter(Cache* cache, unsigned int counter);

#endif
#ifndef SETS_AND_SLOTS
#define SETS_AND_SLOTS

#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::vector;

struct Slot {
    unsigned int tag = 0;
    unsigned int load_ts, access_ts; // timestamps
    bool valid = false;
    bool dirty = false;
};

struct Set {
    vector<Slot> slots;
};

struct Cache {
    vector<Set> sets;
    // std::map<std::string, int> tracker;
    // int num_sets;
    // int num_blocks_per_set;
    // int num_bytes_per_block;
    // bool is_write_allocate;
    // bool is_write_through;
    // bool is_lru; // else, FIFO
};

#endif
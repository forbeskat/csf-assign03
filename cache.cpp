#include <stdexcept>
#include <chrono>
#include <iterator>
#include <cmath>
#include <iostream>
#include "cache.h"

cache::cache(uint32_t num_sets, uint32_t num_blocks_per_set, uint32_t num_bytes_in_block, bool is_lru) {

    this->num_sets = num_sets;
    this->num_blocks_per_set = num_blocks_per_set;
    this->num_bytes_per_block = num_bytes_in_block;
    this->is_lru = is_lru;

    this->total_loads = 0;
    this->total_stores = 0;
    this->load_hits = 0;
    this->load_misses = 0;
    this->store_hits = 0;
    this->store_misses = 0;
    this->total_cycles = 0;
    this->curr_time = 0;


};

// Destructor for the Cache class
cache::~cache() {
    for (Set& set : sets) {
        set.slots.clear(); // Clear the vector of slots in each Set
    }
    sets.clear(); // Clear the vector of Sets
}

/**
 * Start the process by converting the 32 bit trace into a tag, index.
 * This method should the read or write method.
 */
void cache::process_trace_line(uint32_t trace, bool read) {
    int index = get_index_from_trace(trace);
    int tag = get_tag_from_trace(trace);
    
    if (read) {
        read_trace(index, tag);
    } else {
        write_trace(index, tag);
    }
    curr_time++;
}

/* Given a trace, find the the integer value of its index region */
int cache::get_index_from_trace(uint32_t trace) {
    return (trace >> this->num_offset_bits) & ((1 << this->num_index_bits) - 1);
}

/* Given a trace, find the the integer value of its tag region */
int cache::get_tag_from_trace(uint32_t trace) {
    return trace >> num_offset_bits >> num_index_bits;
}
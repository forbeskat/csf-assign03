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

    init_sets();
    calc_index_bits();
    calc_tag_bits();
    calc_offset_bits();
};

// Destructor for the Cache class
cache::~cache() {
    for (Set& set : sets) {
        set.slots.clear(); // Clear the vector of slots in each Set
    }
    sets.clear(); // Clear the vector of Sets
}
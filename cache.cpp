#include <stdexcept>
#include <chrono>
#include <iterator>
#include <cmath>
#include <iostream>
#include "cache.h"

cache::cache(uint32_t num_sets, uint32_t num_blocks_per_set, uint32_t num_bytes_in_block, bool is_lru) {

    this->num_sets = num_sets;

}
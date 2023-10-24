#ifndef BASE_CACHE
#define BASE_CACHE

#include <cstdint>
#include <vector>
#include "sets_and_slots.h"

using std::vector;

/* This file will contain a base class meant to implement a generic cache. The generic cache provides a
*  blueprint for the implementations of the following cache design combinations:
*  1) No-write-allocate + write through 
*  2) Write-allocate + write back
*  3) Write-allocate + write through
*  Reminder: There is no implementation for No-write-allocate + write back
*
*  The implementation of the base class will not include write miss/hit as it is dependent on the cache design combination.
*  The base class implementation will include ~virtual functions for trace read/writes.
*  The base class implementation will include ~virtual functions for total_loads, total_stores, etc...
*/

class cache {
    public:

    /* Constructor for new cache */
    cache(uint32_t num_sets, uint32_t num_blocks_per_set, uint32_t num_bytes_in_block, bool is_lru);

    virtual ~cache();

    /* Process the trace-line by dividing it into the tag, index, etc. */
    void process_trace_line(uint32_t traceline, bool read_no_write);

    int total_loads;
    int total_stores;
    int load_hits;
    int load_misses;
    int store_hits;
    int store_misses;
    int total_cycles;

    /* Initialize cache members */

    Cache newCache;

    int num_sets;
    int num_blocks_per_set;
    int num_bytes_per_block;
    bool is_lru; // else, FIFO

    int num_index_bits;
    int num_tag_bits;
    int num_offset_bits;
    uint32_t curr_time;

    /* Initialize all set objs */

    void init_sets();

    /* Functions to calculate the sizes of the bits */

    void calc_tag_bits();

    void calc_offset_bits();

    void calc_index_bits();

    /* Functions to read and write to memory */

    /* Return set if it is a hit. Otherwise, return null. */

};

#endif
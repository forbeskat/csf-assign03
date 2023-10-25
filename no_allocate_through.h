/* Configuration for no-write-allocate and write-through */

#ifndef NO_ALLOCATE_THROUGH_CACHE
#define NO_ALLOCATE_THROUGH_CACHE

#include "cache.h"
#include <cstdint>

class NO_ALLOCATE_THROUGH_cache : public Cache {
    public:

    /* Constructor */
    NO_ALLOCATE_THROUGH_cache(uint32_t num_sets, uint32_t num_blocks_per_set, uint32_t num_bytes_in_block, bool is_lru) {}

    ~NO_ALLOCATE_THROUGH_cache() {}

    protected:

    void write_trace(uint32_t index, uint32_t tag);
    
    void evict_trace(Set* set, uint32_t tag);
};

#endif

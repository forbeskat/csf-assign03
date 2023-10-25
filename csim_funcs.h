#ifndef CSIM_FUNCS
#define CSIM_FUNCS

#include <string>
#include "cache.h"

/* Check if parameters are valid */
bool has_invalid_param(int argc, char **argv);

/* Used to check if user param is a power of 2 */
bool not_power_of_two(int num);

/* Initialize the cache according to the configurations given by user */
Cache init_cache(char **argv);

int loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset);

void writeThrough(int* totalCycles);

void writeBack(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset);

int loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset);

void noWriteAllocate(int* totalCycles);

/**
     *  Given a tag and index, return the corresponding set if it's 
     *  a hit in the cache. If it's a miss, return a null object. 
*/
bool trace_is_a_hit(uint32_t tag, uint32_t index);

#endif
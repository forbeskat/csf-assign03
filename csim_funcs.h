#ifndef CSIM_FUNCS
#define CSIM_FUNCS

#include <string>
#include "sets_and_slots.h"

using namespace std;

/* Check if parameters are valid */
bool has_invalid_param(int argc, char **argv);

/* Used to check if user param is a power of 2 */
bool not_power_of_two(int num);

/* Initialize the cache according to the configurations given by user */
Cache init_cache(char **argv);

bool loadHit(Cache* cache, unsigned int index, unsigned int tag, unsigned int slotSize, int* total_cycles, unsigned int bytes_in_block, const char* wHit);

void writeThrough(int* totalCycles);

void writeBack(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset);

int loadMiss(Cache* cache, unsigned int index, unsigned int tag, unsigned int offset);

void noWriteAllocate(int* totalCycles);

bool trace_is_a_hit(Cache* cache, unsigned int tag, unsigned int index);

void read_trace(unsigned int index, unsigned int tag);


#endif
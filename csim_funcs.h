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



#endif
#ifndef BASE_CACHE
#define BASE_CACHE

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

#endif
#ifndef SETS_AND_SLOTS
#define SETS_AND_SLOTS

#include <map>
#include <vector>
#include <stdint.h>

using std::vector;

struct Slot {
    uint32_t tag;
    uint32_t load_ts, access_ts; // timestamps
    bool valid = false;
    bool dirty = false;
};

struct Set {
    vector<Slot> slots;
};

struct Cache {
    vector<Set> sets;
};

#endif
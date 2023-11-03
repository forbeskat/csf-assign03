#include "csim_funcs.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// Note: write = store, read = load
int main(int argc, char **argv) {
    if (argc != 7) {
        cerr << "Usage: ./csim num_sets num_blocks num_bytes write/no_write write_through/back eviction" << endl;
        return 1;
    } else if (has_invalid_param(argv)) {
        return 2;
    }

    Cache cache = init_cache(argv);
    unsigned int total_loads = 0;
    unsigned int total_stores = 0;
    unsigned int load_hits = 0;
    unsigned int load_misses = 0;
    unsigned int store_hits = 0;
    unsigned int store_misses = 0;
    unsigned int total_cycles = 0;

    int sets = stoi(argv[1]);
    int blocks = stoi(argv[2]); // blocks = slotsSize
    int bytes_in_block = stoi(argv[3]); // blockSize
    string allocation = argv[4];
    string write_through = argv[5];
    string eviction = argv[6];

    string line;
    int counter = 0;
    
    while(getline(cin, line)) {
        istringstream iss(line);
        string l_or_s;
        unsigned int address;
        unsigned int extra;
        iss >> l_or_s >> std::hex >> address >> extra;

        int bits_index = log2(sets);
        int bits_offset = log2(bytes_in_block);
        int bits_tag = 32 - bits_index - bits_offset;
        unsigned int tag = address >> (bits_index + bits_offset);
        unsigned int index = (address << bits_tag) >> (bits_offset + bits_tag); 
        
        if (bits_offset + bits_tag == 32) {
            index = 0;
        }   
        
        //total_cycles++;
        counter++;
        set_counter(&cache, counter);

        Slot* slot = val_trace_is_a_hit(&cache, tag, index, blocks);
        if (l_or_s == "l"){ // loading
            total_loads++;
            if (slot != NULL) { // memory in cache
                loadHit(&cache, slot, &total_cycles, &load_hits);
            } else { //memory not in cache
                loadMiss(&cache, index, tag, &total_cycles, counter, &load_misses);
            }
        } else if (l_or_s == "s"){ // storing
            total_stores++;
            if (slot != NULL) { // memory in cache
                storeHit(&cache, slot, &total_cycles, &store_hits);
            } else { //memory not in cache
                storeMiss(&cache, index, tag, &total_cycles, counter, &store_misses);
            }
        } else {
            cout << "error: invalid input" << endl;
        }
    }

    cout << "Total loads: " << total_loads << endl;
    cout << "Total stores: " << total_stores << endl;
    cout << "Load hits: " << load_hits << endl;
    cout << "Load misses: " << load_misses << endl;
    cout << "Store hits: " << store_hits << endl;
    cout << "Store misses: " << store_misses << endl;
    cout << "Total cycles: " << total_cycles << endl;
    return 0;
}
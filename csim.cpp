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
    } else if (has_invalid_param(argc, argv)) {
        return 2;
    }

    Cache cache = init_cache(argv);

    int total_loads = 0;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    int total_cycles = 0;

    int sets = stoi(argv[1]);
    int blocks = stoi(argv[2]); // blocks = slotsSize
    int bytes_in_block = stoi(argv[3]); // blockSize
    const char* allocation = argv[4];
    const char* write_through = argv[5];
    std::string eviction = argv[6];
    int indexSize = log2(sets);
    int offsetSize = log2(blocks);
    unsigned int tagSize = 32 - indexSize - offsetSize;

    unsigned int maxTag = (1 << tagSize) - 1;
    unsigned int maxIndex = (1 << indexSize) - 1;

    string line;

    // dirty for write through or evict
    // increment total cycles

    int counter = 0;
    while(getline(cin, line)) {
        istringstream iss(line);
        string l_or_s;
        unsigned int address;
        char r_w;

        //read in a file with the format
        // (l or s) (address) (some other stuff)
        iss >> l_or_s >> address;

        unsigned int tag = (address >> indexSize) & maxTag;
        unsigned int index = address & maxIndex;

        if (!(iss >> r_w >> std::hex >> address)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }

        if (l_or_s == "l"){ // loading
            total_loads++;
            if (trace_is_a_hit(&cache, tag, index)) { // memory in cache
                loadHit(&cache, index, tag, blocks, &total_cycles, bytes_in_block);
            }
        } else if (l_or_s == "s"){ // storing
            total_stores++;
            if (trace_is_a_hit(&cache, tag, index)) { // memory in cache
                total_cycles++;
                storeHit(&cache, index, tag, blocks, &total_cycles, bytes_in_block, allocation, counter);
            } else  {
                storeMiss(&cache, index, tag, blocks, &total_cycles, bytes_in_block, write_through);
            }
        } else {
            cout << "error: invalid input" << endl;
        }

        counter++;
    }

    cout << "Total loads: " << total_loads << endl; // Correct
    cout << "Total stores: " << total_stores << endl;
    cout << "Load hits: " << load_hits << endl;
    cout << "Load misses: " << load_misses << endl;
    cout << "Store hits: " << store_hits << endl;
    cout << "Store misses: " << store_misses << endl;
    cout << "Total cycles: " << total_cycles << endl;

    return 0;
}
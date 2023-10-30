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
    const char* allocation = argv[4];
    const char* write_through = argv[5];
    const char* eviction = argv[6];
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
        unsigned int extra;
        iss >> l_or_s >> std::hex >> address >> extra;


        

        //jank
        // unsigned int tag = (address >> indexSize) & maxTag;
        // unsigned int index = address & maxIndex;
        


        //more jank
        // unsigned int offset = address & ((1 << bytes_in_block) - 1);
        // unsigned int index = (address >> bytes_in_block) & ((1 << indexSize) - 1);
        // unsigned int tag = address >> (bytes_in_block + indexSize);

        // cout<<tag<<" "<<index<<" "<<offset<<" "<<endl;
        
        int bits_index = log2(sets);
        int bits_offset = log2(blocks);
        int bits_tag = 32 - bits_index - bits_offset;
        unsigned int tag = address >> (bits_index + bits_offset);
        unsigned int index = (address << bits_tag) >> (bits_offset + bits_tag); 
        
        if (bits_offset + bits_tag == 32) {
            index = 0;
        }   
        
        
        
        
        // if (!(iss >> r_w >> std::hex >> address)) {
        //     cout<<iss.str()<<endl;
        //     std::cerr << "Error parsing line: " << line << std::endl;
        //     continue;
        // }
        
        total_cycles++;

        if (l_or_s == "l"){ // loading
            total_loads++;
            if (trace_is_a_hit(&cache, tag, index, blocks, counter, eviction)) { // memory in cache
                loadHit(&cache, index, tag, blocks, &total_cycles, bytes_in_block, &load_hits, write_through);
            } else {
                loadMiss(&cache, index, tag, blocks, &total_cycles, bytes_in_block, allocation, counter, &load_misses, eviction);
            }
        } else if (l_or_s == "s"){ // storing
            total_stores++;
            if (trace_is_a_hit(&cache, tag, index, blocks, counter, eviction)) { // memory in cache
                storeHit(&cache, index, tag, blocks, &total_cycles, bytes_in_block, allocation, counter, &store_hits);
            } else {
                storeMiss(&cache, index, tag, blocks, &total_cycles, bytes_in_block, write_through, allocation, counter, &store_misses, eviction);
            }
        } else {
            cout << "error: invalid input" << endl;
        }

        counter++;
        set_counter(&cache, counter);
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
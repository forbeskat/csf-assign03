#include "csim_funcs.h"
#include <iostream>
#include <fstream>
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

    Cache new_cache = init_cache(argv);

    int total_loads;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    int total_cycles = 0;


    string line;

    while(getline(cin, line)) {
        istringstream iss(line);
        string field1;
        string address;
        string someotherstuff; //come back to this thing in part 2
        
        //read in a file with the format
        // (l or s) (address) (some other stuff)
        iss >> field1 >> address >> someotherstuff ;

        if (field1 == "l"){ //loading
            //
        } else if (field1 == "s"){ //storing
            //
        } else {
            cout << "error: invalid input" << endl;
        }


    }

    return 0;
}
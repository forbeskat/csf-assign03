#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

//checks if n is a power of 2
int check_2(int n){
    return (n!= 0) && ((n & (n-1)) == 0);
}

int check_in(int argc, char *argv[]){
    int ret = 0; //i have it set up to specify which error it is. but we probably dont care all that much

    if (argc != 7){
        cerr << "error: invalid number of arguments" << endl;
        ret = 1;
    }

    try {
        if (check_2(atoi(argv[1])) == 0){                 //should it be atoi or stoi idk check before submitting
            cerr << "error: invalid number of sets" << endl;
            ret = 2;
        }
        if (check_2(atoi(argv[2])) == 0){
            cerr << "error: invalid number of blocks" << endl;
            ret = 3;
        }
        if (check_2(atoi(argv[3])) == 0){
            cerr << "error: invalid number of words" << endl;
            ret = 4;
        }
    }
    catch (invalid_argument e) {
        cerr << "error: invalid argument" << endl;
        ret = 5;
    }
    catch (out_of_range e) {
        cerr << "error: out of range" << endl;
        ret = 6;
    }
    
    return ret;
}


void store(string address, vector<string> &cache, int &total_stores, int &store_hits, int &store_misses){
    //store the address in the cache
    //if it's already there, increment store_hits
    //if it's not, increment store_misses
    //increment total_stores
}

int main(int argc, char *argv[]){


    //check if command line input is valid
    if (check_in(argc, argv)){
        return 1;
    }
    
    int total_loads = 0;
    int total_stores = 0;
    int load_hits = 0;
    int load_misses = 0;
    int store_hits = 0;
    int store_misses = 0;
    int total_cycles = 0;


    string line;

    while(getline(cin, line)) {
        istringstream iss(line);
        string ls;
        string address;
        string someotherstuff; //come back to this thing in part 2
        
        //read in a file with the format
        // (l or s) (address) (some other stuff)
        iss >>field1>>address>>someotherstuff ;

        if (ls == "l"){ //loading
            load();
        } else if (field1 == "s"){ //storing
            store();
        } else {
            cerr << "error: invalid input" << endl;
        }
    }

    return 0;
}
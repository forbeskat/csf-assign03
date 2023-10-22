#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int check_in(int argc){
    //check if the input is valid
    //if it is, return 1
    //if it isn't, return 0
    return true;
}
void store(string address, vector<string> &cache, int &total_stores, int &store_hits, int &store_misses){
    //store the address in the cache
    //if it's already there, increment store_hits
    //if it's not, increment store_misses
    //increment total_stores
}


int main(int argc, char *argv[]){


    //check if command line input is valid
    if (!check_in(argc)){
        cerr << "error: invalid input" << endl;
        return 1;
    }




    
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
        string l_or_s;
        string address;
        string someotherstuff; //come back to this thing in part 2
        
        //read in a file with the format
        // (l or s) (address) (some other stuff)
        iss >>field1>>address>>someotherstuff ;

        if (field1 == "l"){ //loading
            load();
        } else if (field1 == "s"){ //storing
            store();
        } else {
            cerr << "error: invalid input" << endl;
        }
    }

    return 0;
}
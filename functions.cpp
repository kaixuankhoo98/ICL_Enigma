#include <iostream>
#include <fstream>
#include <string>
#include "functions.h"
#include "errors.h"
using namespace std;

void load_plugboard(int argc, char *argv[], int plugboard[26], int& number, int& plug_count) {
    // Importing the files into variables
    ifstream in_plugboard;
    in_plugboard.open(argv[1]);
    if (in_plugboard.fail()) {
        cerr << "Sorry, the file " << argv[1] << " could not be opened";
        exit (1);
    }
    
    while (in_plugboard >> number) {
        plugboard[plug_count++] = number;
    }
    
    in_plugboard.close();
}
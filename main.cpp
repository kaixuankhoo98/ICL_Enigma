#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "functions.h"
#include "errors.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc < 7) {
        cerr << "Insufficient number of parameters.";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    // Tests for loading the correct files from the command line
    cout << "The files loaded are: " << endl;
    cout << "Plugboard: " << argv[1] << endl;
    cout << "Reflector: " << argv[2] << endl;
    cout << "Rotors (1, 2 and 3): " << argv[3] 
        << " " << argv[4] << " " << argv[5] << endl;
    cout << "Rotor position: " << argv[6] << "\n" << endl;

    // Importing the files into variables
    int plugboard[26] = {26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26,26}; 
    // Maximum 26 plugboard swaps! Sets any excess plugboards to 26, just outside the range.
    int number, plug_count = 0;
    load_plugboard(argc, argv, plugboard, number, plug_count);
    if (plug_count % 2 == 1) {
        cerr << "Invalid number of plugboard parameters.";
        exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }

    cout << "The plugboard configuration loaded is: ";
    for (int i = 0; i < plug_count; i++) {
        cout << plugboard[i] << " ";
    }

    

    return 0;
}
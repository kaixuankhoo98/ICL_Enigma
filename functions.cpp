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
        exit(ERROR_OPENING_CONFIGURATION_FILE);
    }

    // Checks if there are non-character inputs in the plugboard file
    string plugboard_input;
    getline(ifstream(argv[1]), plugboard_input);
    if (!is_numeric(plugboard_input)) {
        cerr << "The plugboard contains a character other than a number.";
        exit(NON_NUMERIC_CHARACTER);
    } 
    
    // Checks for invalid index
    while (in_plugboard >> number) {
        plugboard[plug_count++] = number;
        for (int i = 0; i < plug_count; i++) {
            if (plugboard[i] >= 26 || plugboard[i] < 0) {
                cerr << "Invalid plugboard index.";
                exit(INVALID_INDEX); 
            }
        }
    }

    // Check for repeating numbers in plugboard (returns impossible plugboard configuration)
    if (plug_count != 0) {
        for (int i = 1; i <= plug_count; i++) {
            for (int j = 0; j <= i-1; j++) {
                if (plugboard[i] == plugboard[j]) {
                    cerr << "Impossible plugboard configuration";
                    exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
                }
            }
        }
    }

    in_plugboard.close();
}

void load_reflector(int argc, char *argv[]) {
    ifstream in_reflector;
    in_reflector.open(argv[2]);

    string reflector_input;
    getline(ifstream(argv[2]), reflector_input);


    in_reflector.close();
}

// Checks if a given input string contains only numbers. (Letters and special characters will return false)
bool is_numeric(string input) {
    for (int i = 0; i < input.length(); i++)
        if (!isdigit(input[i]) && input[i] != ' ')
            return false;
    return true;
}
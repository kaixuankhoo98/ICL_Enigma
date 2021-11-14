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
                exit(INVALID_INDEX); // Checks for invalid index
            }
            if (plug_count !=0) {
                for (int j = 0; j <= i-1; j++) {
                    if (plugboard[i] == plugboard[j]) {
                        cerr << "Impossible plugboard configuration";
                        exit(IMPOSSIBLE_PLUGBOARD_CONFIGURATION);
                    } // Check for repeating numbers in plugboard (returns impossible plugboard configuration)
                }
            }
            
        }
    }
    if (plug_count % 2 == 1) {
        cerr << "Invalid number of plugboard parameters.";
        exit(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS);
    }
    in_plugboard.close();
}

void load_reflector(int argc, char *argv[], int reflector[26], int& number, int& refl_count) {
    ifstream in_reflector;
    in_reflector.open(argv[2]);

    // Checks if there are non-character inputs in the reflector file
    string reflector_input;
    getline(ifstream(argv[2]), reflector_input);
    if (!is_numeric(reflector_input)) {
        cerr << "The reflector contains a character other than a number.";
        exit(NON_NUMERIC_CHARACTER);
    }

    while (in_reflector >> number) {
        reflector[refl_count++] = number;
        for (int i = 0; i < refl_count; i++) {
            if (refl_count !=0) {
                for (int j = 0; j <= i-1; j++) {
                    if (reflector[i] == reflector[j]) {
                        cerr << "Invalid reflector mapping";
                        exit(INVALID_REFLECTOR_MAPPING);
                    }
                }
            }
            if (reflector[i] >= 26 || reflector[i] < 0) {
                cerr << "Invalid reflector index.";
                exit(INVALID_INDEX);
            }
        }
    }
    if (refl_count != 26)
        exit(INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS);

    in_reflector.close();
}

bool is_numeric(string input) {
    for (int i = 0; i < input.length(); i++)
        if (!isdigit(input[i]) && input[i] != ' ')
            return false;
    return true;
}

int load_rotor(char filename[20], int rotor_number) {
    ifstream in_rotor;
    in_rotor.open(filename);
    string rotor_input;
    getline(ifstream(filename), rotor_input);
    int file_length = rotor_input.length();

    for (int i = 0; i < file_length; i++) {
        if (!isdigit(get_file_input_char(filename, i))) {
            return INVALID_INPUT_CHARACTER;
        }
        if (i != 0 && i < 26) {
            for (int j = 0; j < i-1; j++) {
                if (get_file_input(filename, i) == get_file_input(filename, j))
                    return INVALID_ROTOR_MAPPING;
            }
        }
    }
    /* if (!is_rotor_mapping(filename))
        return INVALID_ROTOR_MAPPING; */

    
    in_rotor.close();
    return 0;
}

int notch_count(char filename[20]) {
    ifstream in_rotor;
    in_rotor.open(filename);
    int rotor_count = 0, number, rotor[52];

    while (in_rotor >> number) {
        rotor[rotor_count++] = number;
    }
    in_rotor.close();
    return rotor_count-26;
}

bool is_rotor_mapping(char filename[20]) {
    int count = notch_count(filename);
    ifstream in_rotor;
    in_rotor.open(filename);
    bool legal = true;

    if (count < 0 || count > 26)
        legal = false;
    
    in_rotor.close();
    return legal;
}

bool is_rotor_indexvalid(char filename[20], int index) {
    ifstream in_rotor;
    in_rotor.open(filename);
    bool legal = true;
    int number;
    int rotor[52], rotor_count = 0;

    while (in_rotor >> number) {
        rotor[rotor_count++] = number;
        if (rotor[index] >= 26 || rotor[index] < 0) 
            legal = false;
    }
    in_rotor.close();
    return legal;
}

bool is_numeric(char filename[20], int index) {
    ifstream in_rotor;
    in_rotor.open(filename);
    bool legal = true;
    char loaded_character, full_string[100];
    int length = 0;
    
    while (in_rotor >> loaded_character) {
        full_string[length++] = loaded_character;
    }
    if (!isdigit(full_string[index]) && full_string[index] != ' ')
        legal = false;
    
    // cout << length << " "; 
    in_rotor.close();
    return legal;
} // takes index (of the CHARACTERS in the file) and returns if that is a numeric number (not including whitespace)

int get_file_input(char filename[20], int index) {
    ifstream input;
    input.open(filename);
    int number;
    for (int i = 0; i <= index; i++)
        input >> number;
    return number;
}

char get_file_input_char(char filename[20], int index) {
    ifstream input;
    input.open(filename);
    char number;
    for (int i = 0; i <= index; i++)
        input >> number;
    return number;
}
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "functions1.h"
#include "errors.h"
using namespace std;

string open_file_string(char filename[20]) {
    ifstream input;
    input.open(filename);

    string loaded_input;
    getline(ifstream(filename), loaded_input);

    input.close();
    return loaded_input;
}

int load_plugboard(char filename[20]) {
    string contents = open_file_string(filename);
    cout << "The plugboard loaded contains:\n" << contents << endl; 
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    } // Splits into a vector of strings

    vector<int> inputInts;

    for (int i = 0; i < inputWords.size(); i++) {
        try {inputInts.push_back(stoi(inputWords[i]));} // Convert vector of strings to vector of ints
        catch (invalid_argument &e) {return NON_NUMERIC_CHARACTER;} // Catch in case vector cannot be converted to int
        for (int j = 0; j < inputWords[i].length(); j++) {
            if (!isdigit(inputWords[i][j])) {
                return NON_NUMERIC_CHARACTER;
            }
        }
        if (inputInts[i] < 0 || inputInts[i] >= 26)
            return INVALID_INDEX;
        if (i != 0) {
            for (int j = 0; j < i-1; j++) {
                if (inputInts[i] == inputInts[j]) {
                    return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
                }
            }
        }
    }
    if (inputWords.size() % 2 == 1)
        return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    
    return NO_ERROR;
}

int load_reflector(char filename[20]) {
    string contents = open_file_string(filename);
    cout << "The reflector loaded contains:\n" << contents << endl; 
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    } // Splits into a vector of strings

    vector<int> inputInts;

    for (int i = 0; i < inputWords.size(); i++) {
        try {inputInts.push_back(stoi(inputWords[i]));} // Convert vector of strings to vector of ints
        catch (invalid_argument &e) {return NON_NUMERIC_CHARACTER;} // Catch in case vector cannot be converted to int
        for (int j = 0; j < inputWords[i].length(); j++) {
            if (!isdigit(inputWords[i][j])) {
                return NON_NUMERIC_CHARACTER;
            }
        }
        if (inputInts[i] < 0 || inputInts[i] >= 26)
            return INVALID_INDEX;
        if (i != 0) {
            for (int j = 0; j < i-1; j++) {
                if (inputInts[i] == inputInts[j]) {
                    return INVALID_REFLECTOR_MAPPING;
                }
            }
        }
    }
    if (inputInts.size() != 26)
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    
    return NO_ERROR;
}
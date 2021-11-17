#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "errors.h"
#include "Plugboard.h"
#include "functions.h"
using namespace std;

Plugboard::Plugboard(char filename[20]) {
    name = filename;
    contents = open_file_string(filename);
    
    exit_code = Plugboard::load_plugboard(filename);
    
    insert_to_vector(plugboard_vector, contents);
    length = plugboard_vector.size();
    // print_ints(plugboard_vector); // Use to test that the vector has been loaded correctly
}

int Plugboard::load_plugboard(char filename[20]) {
    string contents = open_file_string(filename);
    // cout << "The plugboard loaded contains:\n" << contents << endl; 
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    } // Splits into a vector of strings

    vector<int> inputInts;

    for (size_t i = 0; i < inputWords.size(); i++) {
        try {inputInts.push_back(stoi(inputWords[i]));} // Convert vector of strings to vector of ints
        catch (invalid_argument &e) {return NON_NUMERIC_CHARACTER;} // Catch in case vector cannot be converted to int
        for (size_t j = 0; j < inputWords[i].length(); j++) {
            if (!isdigit(inputWords[i][j])) {
                return NON_NUMERIC_CHARACTER;
            }
        }
        if (inputInts[i] < 0 || inputInts[i] >= 26)
            return INVALID_INDEX;
        if (i != 0) {
            for (size_t j = 0; j < i-1; j++) {
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

void Plugboard::insert_to_vector(vector<int>& plugboard_vector, string contents) {
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    }

    for (size_t i = 0; i < inputWords.size(); i++) {
        plugboard_vector.push_back(stoi(inputWords[i]));
    }
}

void Plugboard::print_ints(vector<int> plugboard_vector) {
    cout << "The plugboard integers loaded are:\n";
    for (size_t i = 0; i < plugboard_vector.size(); i++) {
        cout << plugboard_vector[i] << " ";
    }
    cout << endl;
}


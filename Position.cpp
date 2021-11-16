#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "errors.h"
#include "Position.h"
#include "functions.h"
using namespace std;

Position::Position(char filename[20], int argc) {
    name = filename;
    contents = open_file_string(filename);
    
    int number_of_rotors = argc-3;

    exit_code = Position::load_position(filename, number_of_rotors);
    insert_to_vector(position_vector, contents);
    // print_ints(position_vector);
}

int Position::load_position(char filename[20], int number_of_rotors) {
    string contents = open_file_string(filename);
    // cout << "The position file loaded contains:\n" << contents << endl; 
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
    }

    if (inputInts.size() < number_of_rotors)
        return NO_ROTOR_STARTING_POSITION;
    
    return NO_ERROR;
}

void Position::insert_to_vector(vector<int>& position_vector, string contents) {
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    }

    for (int i = 0; i < inputWords.size(); i++) {
        position_vector.push_back(stoi(inputWords[i]));
    }
}

void Position::print_ints(vector<int> position_vector) {
    cout << "The position integers loaded are:\n";
    for (int i = 0; i < position_vector.size(); i++) {
        cout << position_vector[i] << " ";
    }
    cout << endl;
}


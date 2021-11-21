#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "errors.h"
#include "Reflector.h"
#include "functions.h"
using namespace std;

Reflector::Reflector(char filename[20]) {
    name = filename;
    contents = open_file_string(filename);

    exit_code = Reflector::load_reflector(filename);

    insert_to_vector(reflector_vector, contents);
    length = reflector_vector.size();
    // print_ints(reflector_vector);
}

int Reflector::load_reflector(char filename[20]) {
    string contents = open_file_string(filename);
    // cout << "The reflector loaded contains:\n" << contents << endl; 
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
        if (i != 0 && i < 26) {
            for (size_t j = 0; j < i-1; j++) {
                if (inputInts[i] == inputInts[j]) {
                    return INVALID_REFLECTOR_MAPPING;
                }
            }
        }
    }
    if (inputInts.size() != 26 || inputInts.size() > 26)
        return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    
    return NO_ERROR;
}

void Reflector::insert_to_vector(vector<int>& reflector_vector, string contents) {
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    }

    for (size_t i = 0; i < inputWords.size(); i++) {
        reflector_vector.push_back(stoi(inputWords[i]));
    }
}

void Reflector::print_ints(vector<int> reflector_vector) {
    cout << "The reflector integers loaded are:\n";
    for (size_t i = 0; i < reflector_vector.size(); i++) {
        cout << reflector_vector[i] << " ";
    }
    cout << endl;
}
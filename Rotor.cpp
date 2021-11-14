#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "errors.h"
#include "Rotor.h"
#include "functions.h"
using namespace std;

Rotor::Rotor(char filename[20]) {
    name = filename;
    contents = open_file_string(filename);
    vector<int> rotor_vector;

    exit_code = Rotor::load_rotor(filename);
    insert_to_vector(rotor_vector, contents);
    // print_ints(rotor_vector);
}

int Rotor::load_rotor(char filename[20]) {
    string contents = open_file_string(filename);
    cout << "The rotor loaded contains:\n" << contents << endl; 
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    } // Splits into a vector of strings

    vector<int> inputInts;

    for (int i = 0; i < inputWords.size(); i++) {
        try {inputInts.push_back(stoi(inputWords[i]));}
        catch (invalid_argument &e) {return NON_NUMERIC_CHARACTER;}
        for (int j = 0; j < inputWords[i].length(); j++) {
            if (!isdigit(inputWords[i][j])) {
                return NON_NUMERIC_CHARACTER;
            }
        }
        if (inputInts[i] < 0 || inputInts[i] >= 26)
            return INVALID_INDEX;
        if (i != 0 && i < 26) {
            for (int j = 0; j < i-1; j++) {
                if (inputInts[i] == inputInts[j]) {
                    return INVALID_ROTOR_MAPPING;
                }
            }
        }
    }
    if (inputInts.size() < 25)
        return INVALID_ROTOR_MAPPING;
    
    return NO_ERROR;
}

void Rotor::insert_to_vector(vector<int>& rotor_vector, string contents) {
    vector<string> inputWords;
    string word;
    stringstream s(contents);
    while (getline(s, word, ' ')) {
        inputWords.push_back(word);
    }

    for (int i = 0; i < inputWords.size(); i++) {
        rotor_vector.push_back(stoi(inputWords[i]));
    }
}

void Rotor::print_ints(vector<int> rotor_vector) {
    cout << "The rotor integers loaded are:\n";
    for (int i = 0; i < rotor_vector.size(); i++) {
        cout << rotor_vector[i] << " ";
    }
    cout << endl;
}
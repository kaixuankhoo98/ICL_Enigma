#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "functions.h"
#include "errors.h"

#include "Plugboard.h"
#include "Reflector.h"
#include "Rotor.h"
#include "Position.h"
using namespace std;

int main(int argc, char** argv) {
    if (argc < 4) {
        cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions";
        exit(INSUFFICIENT_NUMBER_OF_PARAMETERS);
    }

    /*
    int number_of_rotors = 0;
    // Tests for loading the correct files from the command line
    cout << "The files loaded are: " << endl;
    cout << "Plugboard: " << argv[1] << endl;
    cout << "Reflector: " << argv[2] << endl;
    cout << "Rotors: ";
    for (int i = 0; i <= argc-5; i++) {
        cout << argv[3+i] << " ";
        number_of_rotors++;
    } cout << "(Total of " << number_of_rotors << " rotors) " << endl;
    cout << "Rotor position: " << argv[argc-1] << "\n" << endl; */

    if (exit_codes_total(argc, argv) != 0) {
        cerr << "Program exits with Exit Code: " << exit_codes_total(argc, argv);
        return exit_codes_total(argc, argv);
    } 


    string input, converted;
    cout << "Please enter the message you would like to encrypt in all upper-case:" << endl;
    getline(cin >> ws, input);
    int input_exit_code;
    input_exit_code = verify_string(input);

    if (input_exit_code != 0) {
        cerr << "Input exit code: " << input_exit_code;
        return input_exit_code;
    }

    converted = convert_string(input);
    cout << encrypt(converted, argv, argc) << endl;

    return 0;
}
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
        cerr << "Exit code: " << exit_codes_total(argc, argv);
        return exit_codes_total(argc, argv);
    } // Do individual exit codes
    /* if (int exit_pb = exit_code_plugboard(argc, argv) != 0) {
        if (exit_pb == 6) {
            cerr << "Incorrect number of parameters in plugboard file " << argv[1];
            return exit_pb;
        }
        // more
    }
    if (int exit_rf = exit_code_reflector(argc, argv) != 0) {
        if (exit_rf == 9) {
            cerr << "Incorrect (odd) number of parameters in reflector file " << argv[2];
            return exit_rf;
        }
        if (exit_rf == 4) {
            cerr << "Non-numeric character for mapping in rotor file " << argv[2];
            return exit_rf;
        }
    }
    if (int exit_rot = exit_code_rotor(argc, argv) != 0) {
        if (exit_rot == 7) {
            cerr << "Not all inputs mapped in rotor file: "
        }
    } */


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